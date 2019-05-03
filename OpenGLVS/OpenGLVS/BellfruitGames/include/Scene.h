#pragma once
/*!
\file Scene.h
*/
#include <string>

#include "ModelManager.h"
#include "GameObject.h"
#include "ParticleSystemRenderer.h"

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

	AudioComponent* m_audio_music; //!< Audio pointer
	AudioComponent* m_audio_ambience;

	SkyBox* m_skyboxCube; //!< skybox object pointer.
	CameraComponent* m_playerCameraComponent; //!< Player component pointer.
	ModelManager* m_modelmanager; //!< ModelManager pointer.
	ParticleSystemRenderer* m_particleSystem; //!< Manages particles logic and renders them.

	std::vector<GameObject> v_gameObjects; //!< Vector of gameObjects.
	std::vector<GameObject> v_spaceobjects; //!< Vector of gameObjects.
	std::vector<GameObject> v_playerCharacterObjects; //!< Vector of player objects.

	GLSLProgram skyShader; //!< skybox shader.
	GLSLProgram defaultShader; //!< default shader.

	// ---------- physics  ---------------------//

	btTransform m_transform;
	PhysicsBodyComponent* m_physicsBody;
	btCollisionObject* l_collisionObject;
	btRigidBody* l_body;
	btCollisionObject* l_collisionObjectPlayer;
	btRigidBody* l_bodyPlayer;

	// ----------------------------------------//

	int m_score = 0;

public:

	bool hasScored = true;

	WindowSettings& g_window = g_window.getInstance();

	//------------- Shader Components ---------------------------------------------//
	ShaderComponent* framebufferShader; // FBO
	ShaderComponent* framebufferScreenShader; // Screen texture FBO
	ShaderComponent* shaderptr; // Pointer used to  point to all shaders in objects.
	ShaderComponent* debugLineShader;
	ShaderComponent* skyBoxShader;
	//----------------------------------------------------------------------------//

	//! Scene default constructor.
	/*!
	*/
	Scene();

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
	void render();

	void stepPhysicsSimulation();

	void drawCollisionDebugLines();

	void checkIfScored(float dt);
	
	// --- ENTRY FOR LOADING OBJECTS --//
	bool loadSceneObjects(std::string level);

	
	bool loadSpaceObjects(std::string level);
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