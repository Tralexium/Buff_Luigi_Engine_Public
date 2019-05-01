#pragma once
/*!
\file Shader.h
*/

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <glm/mat4x4.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Component.h"
#include "CameraComponent.h"
#include "WindowSettings.h"


using namespace std;

#define CONSTANT 0.8f
#define LINEAR 0.009f
#define QUADRATIC 0.0032f


/*!
\class Scene
\brief Handles shader creation and logic.
*/
class GlowShader : public Component
{
private:

	unsigned int rbo; //!< Rendering Buffer Object
	unsigned int textureColorBufferMultiSampled; //!< Texture Color Buffer Object.
	unsigned int colorBuffers[2];
	unsigned int quadVAO, quadVBO; //!< Quad vertex array object, and vertex buffer object.
	unsigned int  hdrFBO, intermediateFBO; //!< Frame buffer object. (FBO)
	unsigned int screenTexture;

	float constant = CONSTANT;
	float linear = LINEAR;
	float quadratic = QUADRATIC;


	string vertexFileName; //!< file name of vertex shader/
	string fragmentFileName; //!< file name of fragment shader.

	// Default values
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColour = glm::vec3(2.0f, 2.0f, 2.0f);
	glm::vec3 objectColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightDirection = glm::vec3(0.1f, 1.0f, 0.1f);

	glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 specular = glm::vec3(0.1f, 0.1f, 0.1f);

public:
	WindowSettings& g_window = g_window.getInstance(); // Global instance

	void setGlowShaderLightPos(glm::vec3 lp) { lightPos = lp; }
	void setGlowShaderLightColour(glm::vec3 lc) { lightColour = lc; }
	void setGlowShaderObjectColour(glm::vec3 oc) { objectColour = oc; }
	void setGlowShaderLightDirection(glm::vec3 ld) { lightDirection = ld; }

	void setShaderLightAmbient(glm::vec3 amb) { ambient = amb; }
	void setShaderLightDiffuse(glm::vec3 dif) { diffuse = dif; }
	void setShaderLightSpecular(glm::vec3 spec) { specular = spec; }

	void setShaderLightAttenuationConstant(float cons) { constant = cons; }
	void setShaderLightAttenuationLinear(float lin) { linear = lin; }
	void setShaderLightAttenuationQuadratic(float quad) { quadratic = quad; }

	GLuint shaderProgram; //!< shader program id.

	//! Shader class Constructor.
	/*!
	\brief initialisation and creatino of shader.
	\param shadername string that contains the name of the shader.
	*/
	GlowShader(std::string shadername);

	//! Use Shader function.
	/*!
	\brief uses the shader program.
	*/
	void use();

	//! Set uniforms function.
	/*!
	\brief to set or alter different uniforms in the shader program.
	*/
	void setUniforms(const CameraComponent* cam);

	//! Set fbo screen texture function.
	/*!
	*/
	void setfboScreenTexture();

	//! Set fbo texture function.
	/*!
	\brief updates game logic.
	*/
	void setfboTexture();

	void createFBO();

	void createQuad();

	void bindFrameBuffer();

	void unbindFrameBuffer();

	void bindAndDrawFBOQuad();

	void blitFBO();



	//! Overridden Update function.
	/*!
	\brief updates game logic.
	*/
	void OnUpdate(float dt) override {};

	//! Overriden Message Function.
	/*!
	\brief inherited update function.
	\param dt, float for delta time.
	*/
	void OnMessage(const std::string m) override {}

	//! Shader class Destructor.
	/*!
	*/
	~GlowShader();

};



