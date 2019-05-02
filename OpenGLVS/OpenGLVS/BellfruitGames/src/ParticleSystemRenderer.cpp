#include "ParticleSystemRenderer.h"



ParticleSystemRenderer::ParticleSystemRenderer(const unsigned int maxParticles)
{
	resize(maxParticles);
	g_particalPosSizeData = new GLfloat[maxParticles * 4];
	g_particalColorData = new GLubyte[maxParticles * 4];
	initialise();
}

ParticleSystemRenderer::~ParticleSystemRenderer()
{
	if (m_textureID != 0)
	{
		glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}	

	delete[] g_particalPosSizeData;
	delete[] g_particalColorData;

	// Cleanup VBO and shader
	glDeleteBuffers(1, &VBO_billboard);
	glDeleteBuffers(1, &VBO_positionAndSize);
	glDeleteBuffers(1, &VBO_color);
	glDeleteVertexArrays(1, &VAO);
}

void ParticleSystemRenderer::initialise()
{
	// Initialize shader
	m_particleShader = new ShaderComponent("particleShader");
	m_shaderID = m_particleShader->shaderProgram;

	m_particleShader->GetError();

	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// A quad representing the particle to be drawn 
	// only need one, which will be instanced
	static const GLfloat vertexData[] = {
	   -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	   -0.5f, 0.5f, 0.0f,
	   0.5f, 0.5f, 0.0f,
	};

	// The VBO containing the vertex coords
	glGenBuffers(1, &VBO_billboard);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_billboard);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	m_particleShader->GetError();

	// The VBO containing the positions and sizes of the particles
	glGenBuffers(1, &VBO_positionAndSize);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positionAndSize);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(GLfloat) * 4, NULL, GL_STREAM_DRAW);

	m_particleShader->GetError();

	// The VBO containing the colors of the particles
	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(GLubyte) * 4, NULL, GL_STREAM_DRAW);

	m_particleShader->GetError();

	// Generate a texture
	glGenTextures(1, &m_textureID);

	m_particleShader->GetError();
}

void ParticleSystemRenderer::update(float dt)
{
	if (m_particleEmitter != NULL)
	{
		// Emit new particles
		m_particleEmitter->OnUpdate(dt);

		// Shortcut for the emmiter's particle array
		Particle* partContainer = m_particleEmitter->getParticles();

		for (int i = 0; i < m_maxParticles; i++)
		{
			Particle& p = partContainer[i];

			if (p.life > 0.0f)
			{
				p.life -= dt;
				if (p.life > 0.0f)
				{
					// Update particle Position Size and Color
					updateParticle(p, dt);

					// Fill the GPU buffer
					g_particalPosSizeData[4 * partCounter + 0] = p.position.x;
					g_particalPosSizeData[4 * partCounter + 1] = p.position.y;
					g_particalPosSizeData[4 * partCounter + 2] = p.position.z;

					g_particalPosSizeData[4 * partCounter + 3] = p.size;

					g_particalColorData[4 * partCounter + 0] = p.colour.r;
					g_particalColorData[4 * partCounter + 1] = p.colour.g;
					g_particalColorData[4 * partCounter + 2] = p.colour.b;
					g_particalColorData[4 * partCounter + 3] = p.colour.a;
				}
				else {
					// Particles that just died will be put at the end of the buffer inside the emitter
					p.cameraSqDistance = -1.0f;
				}

				partCounter++;
			}
		}

		m_particleEmitter->sortParticles();
	}
}

void ParticleSystemRenderer::render()
{
	// Update the buffers that OpenGL uses for rendering.
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positionAndSize);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(GLfloat) * 4, NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf.
	glBufferSubData(GL_ARRAY_BUFFER, 0, partCounter * sizeof(GLfloat) * 4, g_particalPosSizeData);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(GLubyte) * 4, NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf.
	glBufferSubData(GL_ARRAY_BUFFER, 0, partCounter * sizeof(GLubyte) * 4, g_particalColorData);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	// Use our shader
	glUseProgram(m_shaderID);

	ViewMatrix = m_camera->getViewMatrix();
	ViewProjectionMatrix = m_camera->getProjectionMatrix() * ViewMatrix;

	// Fragment Attributes

	GLuint idz = glGetUniformLocation(m_shaderID, "myTextureSampler");


	if (idz != -1)
	{
		glUniform1i(idz, 0);
	}
	else
	{
		DebugBreak();
	}
	// Vertex Attributes
	glUniform3f(glGetUniformLocation(m_shaderID, "CameraRight_worldspace"), ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
	glUniform3f(glGetUniformLocation(m_shaderID, "CameraUp_worldspace"), ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderID, "VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

	// pass the updated VBO info to the VAO
	setupVAO();

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad -> 1

	if (glGetError() != GL_NO_ERROR)
	{
		DebugBreak();
	}

	//glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, partCounter);
	//glBindVertexArray(0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Keeps track of how many live particles get updated, we reset it after we drew all emitters
	partCounter = 0;

	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
}

void ParticleSystemRenderer::resize(unsigned int newSize)
{
	m_maxParticles = newSize;
}

void ParticleSystemRenderer::updateParticle(Particle& particleData, float dt)
{
	interpolateColor(particleData);

	particleData.position += particleData.velocity * dt;
	particleData.velocity -= glm::vec3(0.0f, 0.1f, 0.0f) * dt;
	particleData.cameraSqDistance = glm::length2(particleData.position - m_camera->getPos());
}

void ParticleSystemRenderer::interpolateColor(Particle& particleData)
{
	colX = particleData.colour;
	colY = particleData.finalColour;
	life = particleData.life;
	increment = (colY - colX) / life;

	colX.x += increment.x; // Red Colour
	colX.y += increment.y; // Green Colour
	colX.z += increment.z; // Blue Colour
	colX.w += increment.w; // Opacity

	particleData.colour = colX;
}

void ParticleSystemRenderer::setEmitter(ParticleEmitterComponent* emitter)
{
	m_particleEmitter = emitter;
	resize(m_particleEmitter->getMaxParticles());
	setTexture(emitter->getTexture());
}

void ParticleSystemRenderer::setCamera(CameraComponent* camera)
{
	m_camera = camera;
}

void ParticleSystemRenderer::setTexture(const std::string & textureFilepath)
{
	// Bind to a Texture ID
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// Load image data and store it to the bound texture ID
	TextureDir = "res/particles/" + textureFilepath + ".png"; //! takes image from filepath, then set neccesary values for 2d texture image
	Bitmap bmp = Bitmap::bitmapFromFile(TextureDir);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.width(), bmp.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.pixelBuffer());

	// Add properties to the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ParticleSystemRenderer::setupVAO()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_billboard);
	glVertexAttribPointer(
		0, // attribute for vertex info.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positionAndSize);
	glVertexAttribPointer(
		1, // attribute for position and size.
		4, // size : x + y + z + size => 4
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glVertexAttribPointer(
		2, // attribute for color.
		4, // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE, // type
		GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0, // stride
		(void*)0 // array buffer offset
	);
}
