#include <iostream>

#include <string>
#include <fstream>
#include <sstream>
#include <glm/detail/type_vec3.hpp>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EngineCore.h"
#include "WindowSettings.h"
#include "MouseSettings.h"


// ------------------- DEFINITION MACROS -------------------------------------------//
#define MOVE_VELOCITY 0.01f // macro for velocity multiplier
#define ROTATE_VELOCITY 0.001f // macro for rotate velocity multiplier
//----------------------------------------------------------------------------------//

// ------------------- GLOBAL Instances --------------------------------------------//
EngineCore* EngineCore::m_pInstance = nullptr; // Initialize enginecore instance to null.
WindowSettings& g_window = g_window.getInstance();
MouseSettings& g_mouse = g_mouse.getInstance();
//---------------------------------------------------------------------------------//

std::vector<bool> EngineCore::m_keyBuffer; // Global key buffer variable.




using namespace std; // using namespace

EngineCore * EngineCore::Instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.

		m_pInstance = new EngineCore;

	return m_pInstance;
}

bool EngineCore::initWindow(int width, int height, std::string windowName)
{
	glfwWindowHint(GLFW_SAMPLES, 4); // Dont think we have to hint it since we are doing offscreen rendering, but keeping it on for now.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	//m_screenWidth = width; // set screen width
	//m_screenHeight = height; // set screen height

	m_window = glfwCreateWindow(g_window.getScreenWidth(), g_window.getScreenHeight(), windowName.c_str(), glfwGetPrimaryMonitor() , nullptr); // create new window

		if (m_window == nullptr)
		{
			std::cout << "Failed to create GLFW m_window" << std::endl;
			glfwTerminate();
			return false;
		}

	glfwMakeContextCurrent(m_window); // make window current context

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialise GLAD" << std::endl;
			return false;
		}

	// Wang UI start --
	m_UIComponent = new UIComponent(); // make new UI componen
	m_UIComponent->initGUI(m_window); //make initialize
	// Wang UI end -


	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, keyCallbackEvent);

	m_keyBuffer.resize(m_keyBufferSize); // make space for the keybuffer
	std::fill(m_keyBuffer.begin(), m_keyBuffer.end(), false);
	// enable depth test
	//glEnable(GL_DEPTH_TEST);

	// enable alpha transparency
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

bool EngineCore::runEngine(BellfruitGame* game)	// was Game&
{
	// -- LOCAL TIMER VARIABLES -----------------------------//
	double l_previousTime = glfwGetTime(); // get time
	static double l_limitFPS = 1.0 / 60.0;
	double l_lastTime = glfwGetTime(), l_timer = l_lastTime;
	double l_deltaTime = 0, l_nowTime = 0;
	int l_frames = 0, l_updates = 0;
	// ------------------------------------------------------//

	// -- Main Game Loop--------------------------------------------------------------------------//
	while (!glfwWindowShouldClose(m_window)) // main game loop
	{

		m_UIComponent->createGUI(); // create GUI context

		// ---------Debug check ms/frame code----------------------------------------------------//
		double l_currentTime = glfwGetTime(); // Measure performance
		l_deltaTime += (l_currentTime - l_lastTime) /l_limitFPS;
		l_lastTime = l_nowTime;
		l_frames++;

			if (l_currentTime - l_previousTime >= 1.0) //if currenttime- previoustime more than 1 sec ago
			{ 
				printf("%f ms/frame\n", 1000.0 / double(l_frames)); // print to console and reset timer.
				l_frames = 0;
				l_previousTime += 1.0;
			}
		//--------------------------------------------------------------------------------------//

			//Mouse move function
		mouseCameraView(game, m_window); // see mouse position.

		// Main Update
		game->update(0.1f); // Main Game,  60 Fps Limited Update function
	
		// Main Render
		game->render(); 

		//Input handler
		game->getPlayerInputHandler()->handleInputs(m_keyBuffer);


		m_UIComponent->renderGUI(); // draw GUI
		if (m_UIComponent->windowOpen == false)
		{
			return false;  // if windowbool is false on exit button, then close window
		}


		glfwSwapBuffers(m_window); // Swap buffers	

		glfwSwapInterval(0); // Enable or Disable Vsync for reduced screentearing!(does cost about double in render performance)

		glfwPollEvents(); // poll for events
	}


	// Update loop!
	while (l_deltaTime >= 1.0)
	{
		{
			game->update(0.1f); // Main Game Update Function!

			l_updates++; // Increment update
			l_deltaTime--; // decrement delta time
		}
			//l_frames++;
	}


	return true;
}


void EngineCore::compileAndLinkSkyBoxShader(GLSLProgram * Shader, string name)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Shader->compileShader(("res/shaders/" + name + ".vert").c_str()); //! Compiles vertex shaders used for the cubemap
	Shader->compileShader(("res/shaders/" + name + ".frag").c_str()); //! Compiles fragment shaders used for the cubemap
	Shader->link(); //! Links the compiled shaders to the GLSLProgram variable
	Shader->validate(); //! Validates the shader has loaded correctly
}

void EngineCore::renderColouredBackground(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EngineCore::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}




//-----------------------------Private functions----------------------------------------------------------------------------------------------------------//



void EngineCore::mouseCameraView(BellfruitGame* game, GLFWwindow * window)
{

	

	// ------------------ Local Variables -----------------------------------------------------------------------------------------------------------------//
	TransformComponent* pTransform = game->getcurrentScene()->getFirstPlayerObject()->getComponent<TransformComponent>(); // pointer to relevant transform.
	CameraComponent* pCamera = game->getcurrentScene()->getFirstPlayerObject()->getComponent<CameraComponent>(); // pointer to camera.

	

	glm::quat orientation = pTransform->getOrientation();
	glm::vec3 position = pTransform->getPosition();
	glm::vec3 relativePosition = game->getcurrentScene()->getFirstPlayerObject()->getRelativePos();

	glfwGetCursorPos(window, &g_mouse.m_currentMouseXpos, &g_mouse.m_currentMouseYpos); //! Built int glfw get cursor pos function.
	float deltaxPos = (float)(g_mouse.m_previousMouseXpos - g_mouse.m_currentMouseXpos); //! delta x mouse pos
	float deltayPos = (float)(g_mouse.m_previousMouseYpos - g_mouse.m_currentMouseYpos); //! delta y mouse pos
	// ---------------------------------------------------------------------------------------------------------------------------------------------------//

	
	//----------------------- Mouse Operations -----------------------------------------------------------------------------------------------------------//
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{

		pTransform->quaternionRotation(deltayPos * ROTATE_VELOCITY, deltaxPos * ROTATE_VELOCITY); // calls rotation function based on x and y mouse positions.
		position += orientation * relativePosition; //changes postition and orientation based on its relative position.
		pCamera->setOri(orientation); // sets orientation of camera while we move x and y.

	}

	g_mouse.m_previousMouseXpos = g_mouse.m_currentMouseXpos; //stores mouse pos x
	g_mouse.m_previousMouseYpos = g_mouse.m_currentMouseYpos;  //stores mouse pos y
	//---------------------------------------------------------------------------------------------------------------------------------------------------//
}

void EngineCore::keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods) // keyboard input
{

	if (key == GLFW_KEY_UNKNOWN || key > m_keyBufferSize)
	{
		return;	
	}
	m_keyBuffer[key] = ((action == GLFW_PRESS || action == GLFW_REPEAT));

	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}*/

}



void EngineCore::drawModel(GLuint shader, Model* model, glm::mat4& modelMatrix) // draw specific models using assimp.
{
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));	// sets shader to model and modelmatrix.
	model->render(shader); // calls render on model.
}

void EngineCore::setSkyBoxMatrices(CameraComponent* camera, GLSLProgram * Shader) // setting specific values for
{
	glm::mat4 projection = glm::perspective(glm::radians(camera->m_fov), g_window.getScreenWidth() / g_window.getScreenHeight(), 0.1f, 1000.0f);
	mat4 mv = camera->getViewMatrix() * model; //! Multiply viewmatrix with modelmatrix
	Shader->setUniform("ModelViewMatrix", mv); //! Set uniform for modelviewmatrix MV
	Shader->setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //! Set uniform for normal matrix
	Shader->setUniform("MVP", projection * mv); //! Set uniform for model view projection matrix by mutiplying MV and P
	mat3 normMat = glm::transpose(glm::inverse(mat3(model))); //! Transpose inverse modelmatrix
	Shader->setUniform("M", model); //! Set uniform for model matrix
	Shader->setUniform("V", camera->getViewMatrix()); //! Set uniform for view matrix
	Shader->setUniform("P", projection); //! Set uniform for projection matrix
	Shader->setUniform("Vskybox", mat4(camera->getViewMatrix())); //! Set uniform for skybox 
}

void EngineCore::resize(CameraComponent* camera, int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	//camera.setAspectRatio((float)w / h);
}

EngineCore::~EngineCore()
{
	//cleanup
	glfwTerminate();
	
}