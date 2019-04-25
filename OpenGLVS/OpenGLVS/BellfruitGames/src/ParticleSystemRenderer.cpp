#include "ParticleSystemRenderer.h"



ParticleSystemRenderer::ParticleSystemRenderer(const unsigned int maxParticles)
{
	m_maxParticles = maxParticles;
	initialise();
}

void ParticleSystemRenderer::initialise()
{
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

	// The VBO containing the positions and sizes of the particles
	glGenBuffers(1, &VBO_positionAndSize);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positionAndSize);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), NULL, GL_STREAM_DRAW);
}

void ParticleSystemRenderer::update(Particle* particleData, int numberOfLiveParticles)
{
	// Update the buffers that OpenGL uses for rendering.
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positionAndSize);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf.
	glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfLiveParticles * sizeof(Particle), particleData);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * sizeof(Particle), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf.
	glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfLiveParticles * sizeof(Particle), particleData);

	// pass the updated VBO info to the VAO
	setupVAO();
}

void ParticleSystemRenderer::setupVAO()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_billboard);
	glVertexAttribPointer(
		0, // attribute. No particular reason for 0, but must match the layout in the shader.
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
		1, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : x + y + z + size => 4
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		sizeof(Particle), // stride
		(void*)0 // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glVertexAttribPointer(
		2, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE, // type
		GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		sizeof(Particle), // stride
		(void*)0 // array buffer offset
	);
}
