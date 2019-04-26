#pragma once
/*!
\file Scene.h
*/
#include <string>

#include "ModelManager.h"
#include "GameObject.h"

#include "ModelComponent.h"
#include "glslprogram.h"
#include "CameraComponent.h"
#include "SkyBox.h"
#include "ShaderComponent.h"
#include "AudioComponent.h"

#include "PhysicsBodyComponent.h"
#include "WindowSettings.h"
/*!
\class Scene
\brief Handles scene logic.
*/
class Scene 
{
private:
	
	std::string levelLoadingfileName = ".json";
	std::string levelLoadingfilePath = "res/levels/";

	AudioComponent* m_audio; //!< Audio pointer
	SkyBox* m_skyboxCube; //!< skybox object pointer.
	CameraComponent* m_playerCameraComponent; //!< Player component pointer.
	ModelManager* m_modelmanager; //!< ModelManager pointer.

	std::vector<GameObject> v_gameObjects; //!< Vector of gameObjects.
	std::vector<GameObject> v_BirdObjects;
	std::vector<GameObject> v_playerCharacterObjects; //!< Vector of player objects.

	GLSLProgram skyShader; //!< skybox shader.
	GLSLProgram defaultShader; //!< default shader.

	// ---------- physics bodies ----------------------//
	btTransform m_transform;
	//btVector3* m_physicsBodyPosition;
	//btQuaternion* m_transform;

	PhysicsBodyComponent* m_physicsBody;



	
	// ------------------------------------------------//
public:
	WindowSettings& g_window = g_window.getInstance();

	//------------- Shader Components -----------------//
	ShaderComponent* framebufferShader; // FBO
	ShaderComponent* framebufferScreenShader; // Screen texture FBO
	ShaderComponent* shaderptr; // Pointer used to  point to all shaders in objects.
	ShaderComponent* debugLineShader;
	// ------------------------------------------------//


	
	
	//! Scene default constructor.
	/*!
	*/
	Scene();

	////! Scene constructor.
	///*!
	//*/
	//Scene(IEngineCore* engineCore);

	//! Scene Destructor.
	/*!
	*/
	~Scene();

	

	//! Update Function.
	/*!
	\param engineInterfacePtr handles rendering.
	*/
	void update(float dt);

	//! Render Function.
	/*!
	\param engineInterfacePtr handles rendering.
	*/
	void render(CameraComponent* camera);

	void stepPhysicsSimulation();

	void drawCollisionDebugLines();

	
	// --- ENTRY FOR LOADING OBJECTS --//
	bool loadSceneObjects(std::string level);



	// --- ENTRY FOR LOADING AI --//
	bool loadAiBirds(std::string level);


	// --- ENTRY FOR LOADING PLAYER  --//
	bool loadPlayerObjects(std::string player);

	//! createModelComponent function.
	/*!
	\brief creates and returns modelcomponent.
	\param string Model* model
	*/
	ModelComponent * createModelComponent(Model *model) { return new ModelComponent(model); }

	// -----Random getter functions ---------------------------------------------//
	GameObject* getFirstPlayerObject() { return &v_playerCharacterObjects[0]; }
	GameObject* getFirstGameObject() { return &v_gameObjects[0]; }
	// --------------------------------------------------------------------------//
};