#include "Scene.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h> 
#include "json/json.h"

#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"

#include "Conversions.h"
#include "EngineCore.h"
#include "MouseSettings.h"

// Global instances
EngineCore* enginecore = enginecore->Instance();
PhysicsWorld& physicsWorld = physicsWorld.getInstance();


Scene::Scene()
{
	m_modelmanager = new ModelManager();  // creating model manager

	//------------ Skybox initialisation -------------//
	//enginecore->compileAndLinkSkyBoxShader(&skyShader, "skyboxShader"); //!Compile and link the skyboxshader
	skyBoxShader = new ShaderComponent("skyboxShader");
	m_skyboxCube = new SkyBox(350.0f, skyBoxShader->shaderProgram); //!Instantiate skybox object
	g_window.GetOpenGLError();
	
	// -- Shader for debug drawing -------------------//
	debugLineShader = new ShaderComponent("lineShader");
	g_window.GetOpenGLError();

	// --------------FBO initalisation --------------------------------------------------------//
	framebufferShader = new ShaderComponent("frameBuffer"); //Instantiate new framebuffer shader
	g_window.GetOpenGLError();
	framebufferShader->createQuad(); // 1. create the quad
	framebufferShader->use(); // 2. use the framebuffer
	framebufferShader->setfboTexture(); // 3.  set the texture

	framebufferScreenShader = new ShaderComponent("framebufferScreen"); //Instantiate new screen framebuffer shader for PP -> for postprocessing
	g_window.GetOpenGLError();
	framebufferShader->createFBO(); // 3.  create fbos
	framebufferScreenShader->use(); // 1.  use second framebuffer for postprocessing
	framebufferScreenShader->setfboScreenTexture(); // 2.  set texture
	
	// ---------------- Initialisation for model loading START--------------- //
	loadSceneObjects(levelLoadingfilePath + "Level_Arena" + levelLoadingfileName);
	loadSpaceObjects(levelLoadingfilePath + "SpaceObjects" + levelLoadingfileName);
	loadPlayerObjects(levelLoadingfilePath + "Player0" + levelLoadingfileName);

	// --------------------- Setting player camera pointer---------------- //
	m_playerCameraComponent = getFirstPlayerObject()->getComponent<CameraComponent>(); // set pointer player camera
	
	// --------------------- Audio stuff -------------------------------- //

	m_audio = new AudioComponent("res/audio/space1.mp3"); // FOR AUDIO

	// --------------------- Particle stuff ----------------------------- //
	m_particleSystem = new ParticleSystemRenderer(100000);
}

















// Main Object Loading Function, handled in Level0.json
bool Scene::loadSpaceObjects(std::string level)
{

	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	jsonData.open(level.c_str());

	// check for errors
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from: "
			<< level
			<< reader.getFormattedErrorMessages();
		return false;
	}

	const Json::Value gameObjects = root["GameObjects"];

	v_spaceobjects.resize(gameObjects.size());

	// size() tells us how large the array is
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//----> name in json file <----//
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";

		//----> the ACTUAL modelname in json <------//
		std::string modelName = gameObjects[i]["model"].asString();

		//----> the ACTUAL modelname in json <------//
		std::string shaderName = gameObjects[i]["shader"].asString();

		//----> the values pos or scale in json <------//
		float x, y, z, w;
		// get the position node
		const Json::Value posNode = gameObjects[i]["position"];
		x = posNode[0].asFloat(); // get float
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();
		glm::vec3 pos(x, y, z);

		// get the position node
		const Json::Value colliderPosNode = gameObjects[i]["colliderposition"];
		x = colliderPosNode[0].asFloat(); // get float
		y = colliderPosNode[1].asFloat();
		z = colliderPosNode[2].asFloat();
		glm::vec3 colpos(x, y, z);

		const Json::Value oriNode = gameObjects[i]["orientation"];
		x = oriNode[0].asFloat(); // get float
		y = oriNode[1].asFloat();
		z = oriNode[2].asFloat();
		w = oriNode[3].asFloat();
		glm::quat ori(x, y, z, w);
		//ori = glm::inverse(ori);

		const Json::Value scaNode = gameObjects[i]["scale"];
		x = scaNode[0].asFloat(); // get float
		y = scaNode[1].asFloat();
		z = scaNode[2].asFloat();
		glm::vec3 sca(x, y, z);

		const Json::Value massNode = gameObjects[i]["mass"];
		x = massNode[0].asFloat(); // get float
		btScalar mass(x);

		const Json::Value colSize = gameObjects[i]["collisionboxsize"];
		x = colSize[0].asFloat(); // get float
		y = colSize[1].asFloat();
		z = colSize[2].asFloat();
		glm::vec3 col(x, y, z);
		const Json::Value NodeX = gameObjects[i]["getX"];
		x = NodeX[0].asFloat(); // get float
		btScalar getX(x);

		const Json::Value NodeY = gameObjects[i]["getY"];
		y = NodeY[0].asFloat(); // get float
		btScalar getY(y);
		//----> the ACTUAL modelname in json <------//
		std::string shapeName = gameObjects[i]["collisionshape"].asString();

		const Json::Value sphereColSizeNode = gameObjects[i]["spherecolsize"];
		if (sphereColSizeNode.type() != Json::nullValue)
		{
			x = sphereColSizeNode[0].asFloat(); // get float
		}
		else x = 1.0f;
		btScalar sphereColSize(x);

		//------------------------- WE LOAD IN OBJECTS THROUGH THE JSON FILE Level0.json----------------------------------------------//

		//--------------- WE ADD IN DEFAULT COMPONENTS TO ALL THESE OBJECTS HERE--- --------------------------------------------------//
		// Because we do v_gameObjects[i] and not a specific one, this will set the components to all objects
		// that this loop goes through, which is every object in the JSON file 

		// All game objects wnats to have these different things such as shaders, models, transforms wants to have a shader, a model
		v_spaceobjects[i].addComponent(new ShaderComponent(shaderName));
		v_spaceobjects[i].addComponent(createModelComponent(m_modelmanager->getModel(modelName))); // get model from manager
		v_spaceobjects[i].addComponent(new TransformComponent(pos, ori, sca)); // pass poss ori scale
		


	}
	return true;

}












// Main Object Loading Function, handled in Level0.json
bool Scene::loadSceneObjects(std::string level)
{

	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	jsonData.open(level.c_str());

	// check for errors
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from: "
			<< level
			<< reader.getFormattedErrorMessages();
		return false;
	}

	const Json::Value gameObjects = root["GameObjects"];

	v_gameObjects.resize(gameObjects.size());

	// size() tells us how large the array is
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//----> name in json file <----//
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";

		//----> the ACTUAL modelname in json <------//
		std::string modelName = gameObjects[i]["model"].asString();

		//----> the ACTUAL modelname in json <------//
		std::string shaderName = gameObjects[i]["shader"].asString();

		//----> the values pos or scale in json <------//
		float x, y, z, w;
		// get the position node
		const Json::Value posNode = gameObjects[i]["position"];
		x = posNode[0].asFloat(); // get float
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();
		glm::vec3 pos(x, y, z);

		// get the position node
		const Json::Value colliderPosNode = gameObjects[i]["colliderposition"];
		x = colliderPosNode[0].asFloat(); // get float
		y = colliderPosNode[1].asFloat();
		z = colliderPosNode[2].asFloat();
		glm::vec3 colpos(x, y, z);

		const Json::Value oriNode = gameObjects[i]["orientation"];
		x = oriNode[0].asFloat(); // get float
		y = oriNode[1].asFloat();
		z = oriNode[2].asFloat();
		w = oriNode[3].asFloat();
		glm::quat ori(x, y, z, w);
		//ori = glm::inverse(ori);

		const Json::Value scaNode = gameObjects[i]["scale"];
		x = scaNode[0].asFloat(); // get float
		y = scaNode[1].asFloat();
		z = scaNode[2].asFloat();
		glm::vec3 sca(x, y, z);

		const Json::Value massNode = gameObjects[i]["mass"];
		x = massNode[0].asFloat(); // get float
		btScalar mass(x);

		const Json::Value colSize = gameObjects[i]["collisionboxsize"];
		x = colSize[0].asFloat(); // get float
		y = colSize[1].asFloat();
		z = colSize[2].asFloat();
		glm::vec3 col(x, y, z);
		const Json::Value NodeX = gameObjects[i]["getX"];
		x = NodeX[0].asFloat(); // get float
		btScalar getX(x);

		const Json::Value NodeY = gameObjects[i]["getY"];
		y = NodeY[0].asFloat(); // get float
		btScalar getY(y);
		//----> the ACTUAL modelname in json <------//
		std::string shapeName = gameObjects[i]["collisionshape"].asString();

		const Json::Value sphereColSizeNode = gameObjects[i]["spherecolsize"];
		if (sphereColSizeNode.type() != Json::nullValue)
		{
			x = sphereColSizeNode[0].asFloat(); // get float
		}
		else x = 1.0f;
		btScalar sphereColSize(x);

		//------------------------- WE LOAD IN OBJECTS THROUGH THE JSON FILE Level0.json----------------------------------------------//

		//--------------- WE ADD IN DEFAULT COMPONENTS TO ALL THESE OBJECTS HERE--- --------------------------------------------------//
		// Because we do v_gameObjects[i] and not a specific one, this will set the components to all objects
		// that this loop goes through, which is every object in the JSON file 

		// All game objects wnats to have these different things such as shaders, models, transforms wants to have a shader, a model
		v_gameObjects[i].addComponent(new ShaderComponent(shaderName));
		v_gameObjects[i].addComponent(createModelComponent(m_modelmanager->getModel(modelName))); // get model from manager
		v_gameObjects[i].addComponent(new TransformComponent(pos, ori, sca)); // pass poss ori scale
		v_gameObjects[i].addComponent(new PhysicsBodyComponent(glmVec3toBt(colpos), glmQuatToBt(ori), glmVec3toBt(sca), mass, glmVec3toBt(col), shapeName, sphereColSize));
		if (i == 4)
		{
			v_gameObjects[i].addComponent(new ParticleEmitterComponent(100, 1, 0.1f, pos, "spark"));
		}
		

	}
	return true;

}



// Main Player loading function, handled in Player0.json
bool Scene::loadPlayerObjects(std::string player)
{
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	jsonData.open(player.c_str());
	// check for errors
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from: "
			<< player
			<< reader.getFormattedErrorMessages();
		return false;
	}

	const Json::Value gameObjects = root["GameObjects"];

	v_playerCharacterObjects.resize(gameObjects.size());

	// size() tells us how large the array is
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//----> name in json file <----//
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";

		//----> the ACTUAL modelname in json <------//
		std::string modelName = gameObjects[i]["model"].asString();

		//----> the ACTUAL modelname in json <------//
		std::string shaderName = gameObjects[i]["shader"].asString();

		//----> the values pos or scale in json <------//
		float x, y, z, w;
		// get the position node
		const Json::Value posNode = gameObjects[i]["position"];
		x = posNode[0].asFloat(); // get float
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();
		glm::vec3 pos(x, y, z);

		// get the position node
		const Json::Value colliderPosNode = gameObjects[i]["colliderposition"];
		x = colliderPosNode[0].asFloat(); // get float
		y = colliderPosNode[1].asFloat();
		z = colliderPosNode[2].asFloat();
		glm::vec3 colpos(x, y, z);

		const Json::Value oriNode = gameObjects[i]["orientation"];
		x = oriNode[0].asFloat(); // get float
		y = oriNode[1].asFloat();
		z = oriNode[2].asFloat();
		w = oriNode[3].asFloat();
		glm::quat ori(x, y, z, w);

		const Json::Value scaNode = gameObjects[i]["scale"];
		x = scaNode[0].asFloat(); // get float
		y = scaNode[1].asFloat();
		z = scaNode[2].asFloat();
		glm::vec3 sca(x, y, z);

		const Json::Value massNode = gameObjects[i]["mass"];
		x = massNode[0].asFloat(); // get float
		btScalar mass(x);

		const Json::Value colSize = gameObjects[i]["collisionboxsize"];
		x = colSize[0].asFloat(); // get float
		y = colSize[1].asFloat();
		z = colSize[2].asFloat();
		glm::vec3 col(x, y, z);

		//----> the ACTUAL modelname in json <------//
		std::string shapeName = gameObjects[i]["collisionshape"].asString();

		const Json::Value sphereColSizeNode = gameObjects[i]["spherecolsize"];
		x = sphereColSizeNode[0].asFloat(); // get float
		btScalar sphereColSize(x);

		//----------------------------------- THIS IS WHERE I LOAD IN PLAYER OBJECTS ---------------------//
		//--------------- ADD COMPONENTS TO LEVEL GAME OBJECTS HERE --------------------------------------//
		v_playerCharacterObjects[i].addComponent(new ShaderComponent(shaderName));
		v_playerCharacterObjects[i].addComponent(createModelComponent(m_modelmanager->getModel(modelName))); // get model from manager
		v_playerCharacterObjects[i].addComponent(new TransformComponent(pos, ori, sca)); // pass poss ori scale
		v_playerCharacterObjects[i].addComponent(new CameraComponent(pos, ori));
		v_playerCharacterObjects[i].addComponent(new PhysicsBodyComponent(glmVec3toBt(colpos), glmQuatToBt(ori), glmVec3toBt(sca), mass, glmVec3toBt(col), shapeName, sphereColSize));
		// -----------------------------------------------------------------------------------------------------------//

		return true;
	}
}


void Scene::stepPhysicsSimulation() {

	
	//-----stepsimulation_start----------------------//
	physicsWorld.getDynamicsWorld()->stepSimulation(1.f / 60.f, 10);

	//print positions of all objects
	for (int j = physicsWorld.getDynamicsWorld()->getNumCollisionObjects() - 2; j >= 0; j--)
	{
		l_collisionObject = physicsWorld.getDynamicsWorld()->getCollisionObjectArray()[j];
		l_body = btRigidBody::upcast(l_collisionObject);

		if (l_body && l_body->getMotionState())
		{
			l_body->getMotionState()->getWorldTransform(physicsWorld.m_transform);
			
			glm::vec3 l_pos(
				(float)physicsWorld.m_transform.getOrigin().getX(),
				(float)physicsWorld.m_transform.getOrigin().getY(),
				(float)physicsWorld.m_transform.getOrigin().getZ());

			glm::quat l_quat(
				
				(float)physicsWorld.m_transform.getRotation().getX(),
				(float)physicsWorld.m_transform.getRotation().getY(),
				(float)physicsWorld.m_transform.getRotation().getZ(),
				(float)physicsWorld.m_transform.getRotation().getW());
		
			// Set position and orientation equal to the physics bodies positions and orientations
			v_gameObjects[j].getComponent<TransformComponent>()->setPos(glm::vec3(-l_pos)); // set Minus pos here to fix some inverse stuff......
			v_gameObjects[j].getComponent<TransformComponent>()->setOri(glm::quat(l_quat));


			////Trying to make a small offset for where the ground gets drawn compared to the collider (not good implementation, only testing)
			//v_gameObjects[0].getComponent<TransformComponent>()->setPos(glm::vec3((float)physicsWorld.m_transform.getOrigin().getX(),
			
		}else
		{
			physicsWorld.m_transform = l_collisionObject->getWorldTransform();
		}
		//printf("world pos object %d = %f,%f,%f\n", j, float(physicsWorld.m_transform.getOrigin().getX()), float(physicsWorld.m_transform.getOrigin().getY()), float(physicsWorld.m_transform.getOrigin().getZ()));
		
		
	}

	// -- IMPORTANT INFO ABOUT THIS SPECIFIC BLOCK OF CODE
	// -- IT IS SORT OF HACKED, BUT IT WILL DO FOR NOW
	// 
	// The arithmetic of l_collisionObjectPlayer after the = sign, is pointing to the last element in the array
	// this last item is going to be the player 
	// The reason behind is because of the ordering of pushing physics objects to the world
	// The player is done last, so he will be the last element pushed to the array.
	// Dont change any of this vector arithmetic below please
	

	// Then IF this is true, then we set this player object relative to the physics component, same way we do for the objects above
	l_collisionObjectPlayer = physicsWorld.getDynamicsWorld()->getCollisionObjectArray()[physicsWorld.getDynamicsWorld()->getNumCollisionObjects() - 1];
	l_bodyPlayer  = btRigidBody::upcast(l_collisionObjectPlayer);

	glm::vec3 l_pos(
		(float)l_collisionObjectPlayer->getWorldTransform().getOrigin().getX(),
		(float)l_collisionObjectPlayer->getWorldTransform().getOrigin().getY(),
		(float)l_collisionObjectPlayer->getWorldTransform().getOrigin().getZ());

	glm::quat l_rot(
		(float)l_collisionObjectPlayer->getWorldTransform().getRotation().getW(),
		(float)l_collisionObjectPlayer->getWorldTransform().getRotation().getX(),
		(float)l_collisionObjectPlayer->getWorldTransform().getRotation().getY(),
		(float)l_collisionObjectPlayer->getWorldTransform().getRotation().getZ());

	if (l_bodyPlayer && l_bodyPlayer->getMotionState())
	{
		l_bodyPlayer->getMotionState()->getWorldTransform(physicsWorld.m_transform);

		v_playerCharacterObjects[0].getComponent<CameraComponent>()->setPos(glm::vec3(l_pos));
		v_playerCharacterObjects[0].getComponent<TransformComponent>()->setPos(glm::vec3(l_pos));
		v_playerCharacterObjects[0].getComponent<CameraComponent>()->setOri(BtQuattoglm(&l_bodyPlayer->getWorldTransform()));
		v_playerCharacterObjects[0].getComponent<TransformComponent>()->setOri(BtQuattoglm(&l_bodyPlayer->getWorldTransform()));

		// TODO SET RIGID BODY ROTATION EQUAL TO CAMERA ROTATION
		//btTransform l_playerTransform = btTransform(glmQuatToBt(v_playerCharacterObjects[0].getComponent<CameraComponent>()->getOri(), glmVec3toBt(v_playerCharacterObjects[0].getComponent<CameraComponent>()->getPos())));
		//l_bodyPlayer->setWorldTransform(l_playerTransform);
	}
	else
	{
		physicsWorld.m_transform = l_collisionObjectPlayer->getWorldTransform();
	}

	//// TODO
	//// ATTEMPTING TO CAST RAYS FROM MOUSE
	//glm::mat4 proj = v_playerCharacterObjects[0].getComponent<CameraComponent>()->getProjectionMatrix();
	//glm::mat4 view = v_playerCharacterObjects[0].getComponent<CameraComponent>()->getViewMatrix();

	//glm::mat4 model;
	//for (int i = 0; i < v_gameObjects.size(); i++)
	//{
	//	model = v_gameObjects[i].getComponent<TransformComponent>()->getModelMatrix();
	//}
	//
	//double l_mouseXpos, l_mouseYpos;
	//glfwGetCursorPos(enginecore->getWindow(), &l_mouseXpos, &l_mouseYpos);

	////physicsWorld.castRays();
	//// CAST RAY FUNCTION 
	//physicsWorld.castRays(mouseToWorldPos
	//(
	//	l_mouseXpos, l_mouseYpos, g_window.getScreenWidth(),
	//	g_window.getScreenHeight(), proj, view, model
	//));

	//cout << l_mouseXpos << l_mouseYpos << endl;
		
}

void Scene::drawCollisionDebugLines() {

	//print positions of all objects
	for (int j = physicsWorld.getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* l_collisionObject = physicsWorld.getDynamicsWorld()->getCollisionObjectArray()[j];

		debugLineShader->use(); // Use debug shader
		debugLineShader->setUniforms(m_playerCameraComponent); // set uniforms
	}
	physicsWorld.drawWorld(); // draw the world
}

// Main Update logic function for scene - Goes on locked 60 FPS instead of maximum cpu framerate (keeps update same across all machines)
void Scene::update(float dt)
{
	//----------------------- Audio Update Logic --------------------------------------------------------------------------------------------------------------------------------------//
	//m_audio->playSound(); 
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	// ---------------------- Physics Update Logic ------------------------------------------------------------------------------------------------------------------------------------//
	stepPhysicsSimulation();
	// --------------------------------------------------------------------------------------------------------------------//
	v_gameObjects[3].OnUpdate(dt);
	v_spaceobjects[0].OnUpdate2(dt);

	// ---------------------- Particle Logic ----------------------------------------------------------------------- //
	m_particleSystem->update(dt);
	// ------------------------------------------------------------------------------------------------------------- //
}

void Scene::render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//------------ BINDING FBO BEFORE RENDERING ANYTHING ---------------------------------------------------------------------------------------------------------------------//
	// Here we bind the framebuffer before we do any rendering, this renders everything into the FBO,
	// So we can then do the shader rendering step with everything getting rendered directly from the FBO.
	framebufferShader->bindFrameBuffer(); //-> Step 1: Bind framebuffer
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

	// ---FOR DRAWING DEBUG LINES AROUND COLLISION BOXES--- //
	//drawCollisionDebugLines();
	// ------------------------------------------------------/
	// ---------- THIS SKYBOX  RENDERING IS SEPERATED, DONT CHANGE ------------------------------------------------------------------------------------------------------------//    
	//skyShader.use();  //! Use skybox shader. 
	//skyBoxShader->setUniforms(m_playerCameraComponent); //! Set matrices for skyshader
	//m_skyboxCube->render(); //!Render Skyshader
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// -------------- Particle Drawing ------------------- //
	for (int i = 0; i < v_spaceobjects.size(); i++)
	{
		Model* model = v_spaceobjects[i].getComponent<ModelComponent>()->getModel(); // pointer to the other models
		GLuint& shader = v_spaceobjects[i].getComponent<ShaderComponent>()->shaderProgram; // get shader program
		shaderptr = v_spaceobjects[i].getComponent<ShaderComponent>();
		shaderptr->use(); // -> Step 2. use shaders specified in loader.
		shaderptr->setShaderComponentLightPos(glm::vec3(0.0f, 12.0f, -5.0f)); // Move light to fourth object whcih is lamp box 
		shaderptr->setUniforms(m_playerCameraComponent); // set uniforms for shader
		glm::mat4 l_modelMatrix = v_spaceobjects[i].getComponent<TransformComponent>()->getModelMatrix(); // get modelMatrix
		enginecore->drawModel(shader, model, l_modelMatrix);	// -> Step3. Draw all models with previous shaders, will be drawn into FBO

		
	}


	// ------------------------ Shader Rendering ----------------------------------------------------------------------------------------------------------------------------//
	// This block of code is responsible for a specific order of rendering the scene into an FBO and then making it a screen texture
	// which is then used to put that texture onto a Quad shape, that Quad shape is then rendering the entire scene as a 800x600 texture
	// or whichever dimension we set it to be in the WindowSettings.h singleton class.
	for (int i = 0; i < v_gameObjects.size(); i++)
	{		
		Model* model = v_gameObjects[i].getComponent<ModelComponent>()->getModel(); // pointer to the other models
		GLuint& shader = v_gameObjects[i].getComponent<ShaderComponent>()->shaderProgram; // get shader program
		shaderptr = v_gameObjects[i].getComponent<ShaderComponent>();
		shaderptr->use(); // -> Step 2. use shaders specified in loader.
		shaderptr->setShaderComponentLightPos(glm::vec3(0.0f, 12.0f, -5.0f)); // Move light to fourth object whcih is lamp box 
		shaderptr->setUniforms(m_playerCameraComponent); // set uniforms for shader
		glm::mat4 l_modelMatrix = v_gameObjects[i].getComponent<TransformComponent>()->getModelMatrix(); // get modelMatrix
		enginecore->drawModel(shader, model, l_modelMatrix);	// -> Step3. Draw all models with previous shaders, will be drawn into FBO

		if (v_gameObjects[i].getComponent<ParticleEmitterComponent>())
		{
			ParticleEmitterComponent* emitter = v_gameObjects[i].getComponent<ParticleEmitterComponent>();
			glm::vec3 pos = v_gameObjects[i].getComponent<TransformComponent>()->getPosition();
			emitter->setEmitterPos(pos);
			m_particleSystem->setEmitter(emitter);
			m_particleSystem->setCamera(m_playerCameraComponent);
			m_particleSystem->render();
		}
	}

	
	// After we have rendered everything and drawn it, we do some additional operations to the FBO, then unbind it.
	framebufferShader->blitFBO(); // -> Step 4. BLIT the fbo
	framebufferShader->unbindFrameBuffer(); // -> Step 5. Unbind the framebuffer, set location back to 0

	// Here the texture will be set to the quad, and render the quads front face as a texture.
	framebufferScreenShader->use();  // -> Step 6. Use the use the framebuffer for the screen texture
	framebufferShader->bindAndDrawFBOQuad(); // -> Step 7. Last step, bind and draw the screen texture FBO.

	// ------------------------------------------------------------------------------------------------------------------------------------------------------------------//

}


Scene::~Scene()
{
	delete m_modelmanager;
	m_modelmanager = nullptr;

	delete m_audio;
	m_audio = nullptr;

	delete m_skyboxCube;
	m_skyboxCube = nullptr;

	delete framebufferShader;
	framebufferShader = nullptr;

	delete framebufferScreenShader;
	framebufferScreenShader = nullptr;




	for (GameObject gameObject : v_gameObjects)
	{
		if (gameObject.getComponent<TransformComponent>())
		{
			delete gameObject.getComponent<TransformComponent>();

			v_gameObjects.clear();
		}
		if (gameObject.getComponent<ModelComponent>())
		{
			delete gameObject.getComponent<ModelComponent>();

			v_gameObjects.clear();
		}
		if (gameObject.getComponent<ShaderComponent>())
		{
			delete gameObject.getComponent<ShaderComponent>();

			v_gameObjects.clear();
		}

		if (gameObject.getComponent<PhysicsBodyComponent>())
		{
			delete gameObject.getComponent<PhysicsBodyComponent>();

			delete m_physicsBody;
			m_physicsBody = nullptr;

			v_gameObjects.clear();
		}


	}

	for (GameObject playerObject : v_playerCharacterObjects)
	{
		if (playerObject.getComponent<TransformComponent>())
		{
			delete playerObject.getComponent<TransformComponent>();

			v_playerCharacterObjects.clear();
		}
		if (playerObject.getComponent<ModelComponent>())
		{
			delete playerObject.getComponent<ModelComponent>();
			
			v_playerCharacterObjects.clear();
		}
		if (playerObject.getComponent<ShaderComponent>())
		{
			delete playerObject.getComponent<ShaderComponent>();

			v_playerCharacterObjects.clear();
		}
		if (playerObject.getComponent<PhysicsBodyComponent>())
		{
			delete playerObject.getComponent<PhysicsBodyComponent>();

			delete m_physicsBody;
			m_physicsBody = nullptr;

			v_playerCharacterObjects.clear();
		}

	}

	delete m_physicsBody;
	m_physicsBody = nullptr;
	delete l_collisionObject;
	l_collisionObject = nullptr;
	delete l_body;
	l_body = nullptr;
	delete l_collisionObjectPlayer;
	l_collisionObjectPlayer = nullptr;
	delete l_bodyPlayer;
	l_bodyPlayer = nullptr;


}

