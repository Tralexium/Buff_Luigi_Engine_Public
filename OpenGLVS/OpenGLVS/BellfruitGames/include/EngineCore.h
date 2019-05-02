#pragma once
#define GLFW_INCLUDE_NONE
/*!
\file EngineCore.h
*/
#include "glslprogram.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>


#include "Scene.h"
#include "Model.h"
#include "CameraComponent.h"
#include "BellfruitGame.h"
//#include "PhysicsBodyComponent.h"

/*!
\class EngineCore
\brief handles all core related tasks such OpenGL instructions and running main game loop.
*/
class EngineCore
{	
private:

	EngineCore() {};  // Private so that it can  not be called

	EngineCore(EngineCore const&) {};             // copy constructor is private

	EngineCore& operator=(EngineCore const&) {};  // assignment operator is private

	static EngineCore* m_pInstance;

	//! frame buffer size callback for resizing window.
	/*!
	\param window ptr to window object.
	\param width
	\param height
	*/
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//! Static mouse callback for mouse input.
	/*!
	\param window ptr to window object.
	\param xPos - position of x coordinate of mouse.
	\param yPos - position of y coordinate of mouse.
	*/
	static void mouseCameraView(BellfruitGame* game, GLFWwindow* window);

	//! Static key callback for keyboard input.
	/*!
	\param window ptr to window object.
	\param key keycodes for keyboard.
	\param scancode
	\param action
	\param mods
	*/
	static void keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	static EngineCore * Instance();

	static std::vector<bool> m_keyBuffer; //!< key buffer.
	GLuint m_defaultSP; //!< GLuint default shader.
	GLuint programHandle; //!< Program handle.

	int width, height; //!< int height variables.
	static const int m_keyBufferSize = 400; //!< key buffer size.
	GLFWwindow* m_window;  //!< GLFWwindow pointer variable.
	mat4 model; //!< Model Matrix.

	int m_screenWidth;  //!< screen width.
	int m_screenHeight; //!< screen height.

	//! Initializes window.
	/*!
	\param width width of window.
	\param height height of window.
	\param param windowName name of the window.
	*/
	bool initWindow( int width, int height, std::string windowName);

	//! Run the engine.
	/*!
	\param game reference to game class.
	*/
	bool runEngine(BellfruitGame* game);

	//! Renders coloured background.
	/*!
	\param r red.
	\param g green.
	\param b blue.
	*/
	void renderColouredBackground(float r, float g, float b);
	
	//! Skybox Settings function.
	/*!
	\param *camera passing pointer to camera component
	\param  *shader passing pointer to shader
	*/
	void setSkyBoxMatrices(CameraComponent* camera, GLSLProgram* Shader);

	//! Compile and link shader function.
	/*!
	\brief compiles and links the GLSL shader program
	\param shader GLSL shader pointer
	\param name string variable to hold name of shader
	*/
	void compileAndLinkSkyBoxShader(GLSLProgram* Shader, string name);
		
	//! Draws model to screen.
	/*!
	\param model model pointer.
	\param modelMatrix the model matrix.
	*/
	void drawModel(GLuint shader, Model* model, glm::mat4& modelMatrix);

	//! Reize Window Function.
	/*!
	\brief resize the window based on camera view.
	\param *camera Pointer to camera component
	\param w width of screen
	\param h height of screen
	*/
	void resize(CameraComponent* camera, int w, int h);

	GLFWwindow* getWindow() { return m_window; }

	//! Virtual Destructor.
	/*!
	*/
	virtual ~EngineCore();
};

