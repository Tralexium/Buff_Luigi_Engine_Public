#include "ShaderComponent.h"



ShaderComponent::ShaderComponent(std::string shadername)
{
	// initialize lights

	//load from files
	vertexFileName = "res/shaders/" + shadername + ".vert";
	fragmentFileName = "res/shaders/" + shadername + ".frag";

	// Load contents of vertex file
	std::ifstream inFile(vertexFileName);
	if (!inFile) {
		string errorMsg = "Error opening shader file: " + vertexFileName + "\n";
		fprintf(stderr, errorMsg.c_str());
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	std::string codeStr(code.str());
	const GLchar* vertex_shader[] = { codeStr.c_str() };

	// Load contents of fragment file
	std::ifstream inFile2(fragmentFileName);
	if (!inFile2) {
		string errorMsg = "Error opening shader file: " + fragmentFileName + "\n";
		fprintf(stderr, errorMsg.c_str());
		exit(1);
	}

	std::stringstream code2;
	code2 << inFile2.rdbuf();
	inFile2.close();
	std::string codeStr2(code2.str());
	const GLchar* fragment_shader[] = { codeStr2.c_str() };

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertex_shader, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragment_shader, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader); // clean up
	glDeleteShader(fragmentShader); // clean up
}

void ShaderComponent::use() // loading some default shaders to get things up and running
{
	glUseProgram(shaderProgram);// set the default shader
}

void ShaderComponent::setfboScreenTexture() 
{
	glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);
}

void ShaderComponent::setfboTexture() 
{
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1_diffuse"), 0);
}

void ShaderComponent::createQuad() 
{

	float quadVertices[] =
	{
		// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// screen quad VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

void ShaderComponent::bindFrameBuffer() 
{
	// These steps need to be followed for the FBO to render!
	// 1. Bind Framebuffer!
	glBindFramebuffer(GL_FRAMEBUFFER, msFBO);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // make sure we clear the framebuffer's content
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)	
}

void ShaderComponent::unbindFrameBuffer() 
{
	// 3. Unbind Framebuffer!
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
}

void ShaderComponent::bindAndDrawFBOQuad() 
{
	// 5. Bind quad QUAD vao and textureColorbuffer, then draw it!
	glBindVertexArray(quadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, screenTexture); // use the now resolved color attachment as the quad's texture
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ShaderComponent::blitFBO() 
{
	// 2.5 now blit multisampled buffer(s) to normal colorbuffer of intermediate FBO. Image is stored in screenTexture
	glBindFramebuffer(GL_READ_FRAMEBUFFER, msFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
	glBlitFramebuffer(0, 0, g_window.getScreenWidth(), g_window.getScreenHeight(), 0, 0, g_window.getScreenWidth(), g_window.getScreenHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void ShaderComponent::createFBO() 
{
	// Start MSAA FBO
	// 1.
	// configure MSAA framebuffer
	glGenFramebuffers(1, &msFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, msFBO);

	// 2.
	// create a multisampled color attachment texture
	glGenTextures(1, &textureColorBufferMultiSampled);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, g_window.getScreenWidth(), g_window.getScreenHeight(), GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);

	// 3.
	// create a (also multisampled) renderbuffer object for depth and stencil attachments
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, g_window.getScreenWidth(), g_window.getScreenHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// 4.
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//--------------------------------------------------------------------------------------------------------//
	// Start PostProcessing FBO
	// 1. 
	// Configure second FBO so we can do postprocessing effects still
	glGenFramebuffers(1, &intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);

	// 2.
	// create a color attachment texture
	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, g_window.getScreenWidth(), g_window.getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);	// we only need a color buffer


	// 3. 
	// Check if any errors with the intermediate FBO
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShaderComponent::setUniforms(const CameraComponent * cam)
{
	// set the view and projection components of our shader to the CameraComponent values
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(cam->getProjectionMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cam->getViewMatrix()));

	glUniform3f(glGetUniformLocation(shaderProgram, "light.objectColour"), objectColour.x, objectColour.y, objectColour.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "light.lightColour"), lightColour.x, lightColour.y, lightColour.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "light.lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "light.lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 0, glm::value_ptr(cam->getPos()));

	glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"), ambient.x, ambient.y, ambient.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "light.specular"), specular.x, specular.y, specular.z);

	glUniform1f(glGetUniformLocation(shaderProgram, "light.constant"), constant);
	glUniform1f(glGetUniformLocation(shaderProgram, "light.linear"), linear);
	glUniform1f(glGetUniformLocation(shaderProgram, "light.quadratic"), quadratic);
}

ShaderComponent::~ShaderComponent()
{

	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
	glDeleteBuffers(1, &msFBO);
	glDeleteBuffers(1, &textureColorBufferMultiSampled);
}

string ShaderComponent::GetError()
{
	// opengl doesn't report error conditions, you have
	// to ask for any errors - this will return
	// a string representing any open gl errors found
	// if all is ok you get the empty string

	string s = "";
	GLenum err;
	err = glGetError();

	if (err == GL_NO_ERROR)
	{
		return s;
	}

	DebugBreak();	//want to know about the error - set a breakpoint here while debugging

					// loop scanning for errors and appending them to a string
	while ((err != GL_NO_ERROR) && (s.length() < 128)) // stop infinite loop!!
	{
		switch (err)
		{
		case GL_NO_ERROR:
			//"No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
			break;

		case GL_INVALID_ENUM:
			s = s + "GL_INVALID_ENUM "; //"An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
			break;

		case GL_INVALID_VALUE:
			s = s + "GL_INVALID_VALUE "; //"A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
			break;

		case GL_INVALID_OPERATION:
			s = s + "GL_INVALID_OPERATION "; //"The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
			break;

			//case GL_INVALID_FRAMEBUFFER_OPERATION:
			//    s = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
			//    break;

		case GL_OUT_OF_MEMORY:
			s = s + "GL_OUT_OF_MEMORY "; //"There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
			break;

		case GL_STACK_UNDERFLOW:
			s = s + "GL_STACK_UNDERFLOW";	//"An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;

		case GL_STACK_OVERFLOW:
			s = s + "GL_STACK_OVERFLOW"; //"An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		}
		// get next error, if any
		err = glGetError();
	}
	// return the error messages as a single string
	return s;
}
