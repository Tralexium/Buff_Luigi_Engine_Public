#include "Scene.h"
#include <fstream>
#include <iostream>
#include <sstream>
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

#include "PhysicsWorld.h"

EngineCore* enginecore = enginecore->Instance();

PhysicsWorld& physicsWorld = physicsWorld.getInstance();


Scene::Scene()
{
	m_modelmanager = new ModelManager();  // creating model manager

	//------------ Skybox initialisation -------------//
	enginecore->compileAndLinkSkyBoxShader(&skyShader, "skyboxShader"); //!Compile and link the skyboxshader
	m_skyboxCube = new SkyBox(350.0f, skyShader.getHandle()); //!Instantiate skybox object
	
	// -- Shader for debug drawing --//
	debugLineShader = new ShaderComponent("lineShader");

	// --------------FBO initalisation ------//
	framebufferShader = new ShaderComponent("frameBuffer"); // Instantiate new framebuffer shader
	framebufferShader->createQuad(); // 1. create the quad
	framebufferShader->use(); // 2. use the framebuffer
	framebufferShader->setfboTexture(); // 3.  set the texture

	framebufferScreenShader = new ShaderComponent("framebufferScreen"); //  Instantiate new screen framebuffer shader for PP -> for postprocessing
	framebufferShader->createFBO(); // 3.  create fbos
	framebufferScreenShader->use(); // 1.  use second framebuffer for postprocessing
	framebufferScreenShader->setfboScreenTexture(); // 2.  set texture
	
	//---------------- Initialisation for model loading START---------------//
	loadSceneObjects(levelLoadingfilePath + "Level0" + levelLoadingfileName);
	loadPlayerObjects(levelLoadingfilePath + "Player0" + levelLoadingfileName);
	loadAiBirds(levelLoadingfilePath + "AIObjects" + levelLoadingfileName);
	// --------------------- Setting player camera pointer----------------//
	m_playerCameraComponent = getFirstPlayerObject()->getComponent<CameraComponent>(); // set pointer player camera
	
	// --------------------- Audio stuff --------------------------------//
	m_audio = new AudioComponent("res/audio/space1.mp3"); // FOR AUDIO

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



		//------------------------- WE LOAD IN OBJECTS THROUGH THE JSON FILE Level0.json----------------------------------------------//

		//--------------- WE ADD IN DEFAULT COMPONENTS TO ALL THESE OBJECTS HERE--- --------------------------------------------------//

		// Because we do v_gameObjects[i] and not a specific one, this will set the components to all objects
		// that this loop goes through, which is every object in the JSON file 

		// All game objects wnats to have these different things such as shaders, models, transforms wants to have a shader, a model
		v_gameObjects[i].addComponent(new ShaderComponent(shaderName));
		v_gameObjects[i].addComponent(createModelComponent(m_modelmanager->getModel(modelName))); // get model from manager
		v_gameObjects[i].addComponent(new TransformComponent(pos, ori, sca)); // pass poss ori scale
		v_gameObjects[i].addComponent(new PhysicsBodyComponent(glmVec3toBt(colpos), glmQuatToBt(ori), glmVec3toBt(sca), mass, glmVec3toBt(col)));



	}
	return true;

}



// Main Object Loading Function, handled in Level0.json
bool Scene::loadAiBirds(std::string level)
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

	v_BirdObjects.resize(gameObjects.size());

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

		const Json::Value NodeX = gameObjects[i]["getX"];
		x = NodeX[0].asFloat(); // get float
		btScalar getX(x);
	
		const Json::Value NodeY = gameObjects[i]["getY"];
		y = NodeY[0].asFloat(); // get float
		btScalar getY(y);
		

		//------------------------- WE LOAD IN OBJECTS THROUGH THE JSON FILE Level0.json----------------------------------------------//

		//--------------- WE ADD IN DEFAULT COMPONENTS TO ALL THESE OBJECTS HERE--- --------------------------------------------------//

		// Because we do v_gameObjects[i] and not a specific one, this will set the components to all objects
		// that this loop goes through, which is every object in the JSON file 

		// All game objects wnats to have these different things such as shaders, models, transforms wants to have a shader, a model
		v_BirdObjects[i].addComponent(new ShaderComponent(shaderName));
		v_BirdObjects[i].addComponent(createModelComponent(m_modelmanager->getModel(modelName))); // get model from manager
		v_BirdObjects[i].addComponent(new TransformComponent(pos, ori, sca)); // pass poss ori scale
	
		
		

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


		//----> the values pos or scale in json <------//
		float x, y, z, w;
		// get the position node
		const Json::Value posNode = gameObjects[i]["CameraPosition"];
		x = posNode[0].asFloat(); // get float
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();
		glm::vec3 CameraPosition(x, y, z);

		const Json::Value oriNode = gameObjects[i]["CameraOrientation"];
		x = oriNode[0].asFloat(); // get float
		y = oriNode[1].asFloat();
		z = oriNode[2].asFloat();
		w = oriNode[3].asFloat();
		glm::quat CameraOrientation(x, y, z, w);

		const Json::Value playerPosNode = gameObjects[i]["PlayerPosition"];
		x = playerPosNode[0].asFloat(); // get float
		y = playerPosNode[1].asFloat();
		z = playerPosNode[2].asFloat();
		glm::vec3 pos(x, y, z);

		const Json::Value playerOriNode = gameObjects[i]["PlayerOrientation"];
		x = playerOriNode[0].asFloat(); // get float
		y = playerOriNode[1].asFloat();
		z = playerOriNode[2].asFloat();
		w = playerOriNode[3].asFloat();
		glm::quat ori(x, y, z, w);

		const Json::Value scaNode = gameObjects[i]["scale"];
		x = scaNode[0].asFloat(); // get float
		y = scaNode[1].asFloat();
		z = scaNode[2].asFloat();
		glm::vec3 sca(x, y, z);

		//const Json::Value massNode = gameObjects[i]["mass"];
		//x = massNode[0].asFloat(); // get float
		//btScalar mass(x);


		//----------------------------------- THIS IS WHERE I LOAD IN PLAYER OBJECTS ---------------------//
		//--------------- ADD COMPONENTS TO LEVEL GAME OBJECTS HERE --------------------------------------//
		v_playerCharacterObjects[i].addComponent(new TransformComponent(CameraPosition, CameraPosition, sca)); // pass poss ori scale
		v_playerCharacterObjects[i].addComponent(new CameraComponent(CameraPosition, CameraOrientation));

		// -----------------------------------------------------------------------------------------------------------//


	}
	return true;

}



void Scene::stepPhysicsSimulation() {

	
	//-----stepsimulation_start----------------------//
	physicsWorld.getDynamicsWorld()->stepSimulation(1.f / 60.f, 10);

	//print positions of all objects
	for (int j = physicsWorld.getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; j--)
	{

		btCollisionObject* l_collisionObject = physicsWorld.getDynamicsWorld()->getCollisionObjectArray()[j];
		btRigidBody* l_body = btRigidBody::upcast(l_collisionObject);

		if (l_body && l_body->getMotionState())
		{
			l_body->getMotionState()->getWorldTransform(physicsWorld.m_transform);
			
			glm::vec3 l_pos((float)physicsWorld.m_transform.getOrigin().getX(), 
							(float)physicsWorld.m_transform.getOrigin().getY(), 
							(float)physicsWorld.m_transform.getOrigin().getZ());

			glm::quat l_quat((float)physicsWorld.m_transform.getRotation().getW(), 
							 (float)physicsWorld.m_transform.getRotation().getX(), 
							 (float)physicsWorld.m_transform.getRotation().getY(), 
							 (float)physicsWorld.m_transform.getRotation().getZ());

			

			v_gameObjects[j].getComponent<TransformComponent>()->setPos(glm::vec3(l_pos));
			v_gameObjects[j].getComponent<TransformComponent>()->setOri(glm::quat(l_quat));

			v_gameObjects[0].getComponent<TransformComponent>()->setPos(glm::vec3((float)physicsWorld.m_transform.getOrigin().getX(),
				(float)physicsWorld.m_transform.getOrigin().getY() +0.8,
				(float)physicsWorld.m_transform.getOrigin().getZ()));
		}

		else
		{
			physicsWorld.m_transform = l_collisionObject->getWorldTransform();
		}

		//printf("world pos object %d = %f,%f,%f\n", j, float(physicsWorld.m_transform.getOrigin().getX()), float(physicsWorld.m_transform.getOrigin().getY()), float(physicsWorld.m_transform.getOrigin().getZ()));
	}
}

void Scene::drawCollisionDebugLines() {

	//print positions of all objects
	for (int j = physicsWorld.getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* l_collisionObject = physicsWorld.getDynamicsWorld()->getCollisionObjectArray()[j];

		debugLineShader->use(); // Use debug shader
		debugLineShader->setUniforms(m_playerCameraComponent); // set uniforms

		//// Use drawline function from btIDebugDraw
		//physicsWorld.getPhysicsWorldDebugDrawer()->drawLine
		//(
		//	btVector3
		//	(
		//	0,0,0
		//	),
		//	btVector3
		//	(
		//	0,0,0
		//	),
		//	btVector3(10, 0, 0)
		//);
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

	// --------------------------------------------------------------------------------------------------------------------

	v_BirdObjects[1].OnUpdate(dt);
	v_BirdObjects[2].OnUpdate2(dt);


}


void Scene::render(CameraComponent* camera)
{
	//------------ BINDING FBO BEFORE RENDERING ANYTHING ---------------------------------------------------------------------------------------------------------------------//
	// Here we bind the framebuffer before we do any rendering, this renders everything into the FBO,
	// So we can then do the shader rendering step with everything getting rendered directly from the FBO.
	framebufferShader->bindFrameBuffer(); //-> Step 1: Bind framebuffer
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	// ---FOR DRAWING DEBUG LINES AROUND COLLISION BOXES--- //
	drawCollisionDebugLines();
	// ------------------------------------------------------//


	// ---------- THIS SKYBOX  RENDERING IS SEPERATED, DONT CHANGE ------------------------------------------------------------------------------------------------------------//    
	skyShader.use();  //! Use skybox shader. 
	enginecore->setSkyBoxMatrices(m_playerCameraComponent, &skyShader); //! Set matrices for skyshader
	m_skyboxCube->render(); //!Render Skyshader
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

	for (int i = 0; i < v_BirdObjects.size(); i++)
	{

		Model* birdModel = v_BirdObjects[i].getComponent<ModelComponent>()->getModel(); // pointer to the other models
		GLuint& birdShader = v_BirdObjects[i].getComponent<ShaderComponent>()->shaderProgram; // get shader program
		shaderptr = v_BirdObjects[i].getComponent<ShaderComponent>();

		shaderptr->use(); // -> Step 2. use shaders specified in loader.

		shaderptr->setUniforms(m_playerCameraComponent); // set uniforms for shader
		glm::mat4 l_modelMatrix = v_BirdObjects[i].getComponent<TransformComponent>()->getModelMatrix(); // get modelMatrix
		enginecore->drawModel(birdShader, birdModel, l_modelMatrix);	// -> Step3. Draw all models with previous shaders, will be drawn into FBO

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

		shaderptr->setShaderComponentLightPos(glm::vec3(v_gameObjects[4].getComponent<TransformComponent>()->getPosition())); // Move light to fourth object whcih is lamp box 
		shaderptr->setUniforms(m_playerCameraComponent); // set uniforms for shader
		glm::mat4 l_modelMatrix = v_gameObjects[i].getComponent<TransformComponent>()->getModelMatrix(); // get modelMatrix


		

		enginecore->drawModel(shader, model, l_modelMatrix);	// -> Step3. Draw all models with previous shaders, will be drawn into FBO

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
			//delete m_transform;
			//m_transform = nullptr;
			delete m_physicsBody;
			m_physicsBody = nullptr;
			//delete m_physicsBodyPosition;


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
			//delete m_transform;
			//m_transform = nullptr;
			delete m_physicsBody;
			m_physicsBody = nullptr;
			//delete m_physicsBodyPosition;

			v_playerCharacterObjects.clear();
		}

	}




}

