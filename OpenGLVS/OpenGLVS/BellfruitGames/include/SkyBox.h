#pragma once
/*!
\file SkyBox.h
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include "CameraComponent.h"
#include <string>
#include <cstdio>

using glm::vec3;
using glm::mat3;
using glm::mat4;

/*!
\class Scene
\briefhandles creation and setting up the skybox.
*/
class SkyBox 
{

private:

	unsigned int vaoHandle; //!< unsigned vaoHandle integer.
	int faces = 6; //!< faces integer.
	GLuint textureID; //!< opengl integer for textureID.

public:

	//! Default Constructor.
	/*!
	*/
	SkyBox() {};

	//! Constructor.
	/*!
	\brief handles vertices and shader id.
	\param fvert the vertices of the cube.
	\param shader the value of the shader id.
	*/
	SkyBox(int fvert, unsigned int shader);



	//! Destructor.
	/*!
	*/
	~SkyBox() {};

	//! Render Function.
	/*!
	\brief handles rendering of the cube.
	*/
	void render() const;

};
