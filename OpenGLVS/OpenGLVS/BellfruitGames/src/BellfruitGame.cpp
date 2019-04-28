#include "BellfruitGame.h"


BellfruitGame::BellfruitGame()
{
	
	m_currentScene = new Scene(); // create new scene	


	

	m_playerInputHandler = new InputHandler(m_currentScene->getFirstPlayerObject()); //! handles input on the 1 game object		
	m_menuInputHandler = new InputHandler(m_currentScene->getFirstMenuObject()); //! handles input on the 1 game object		

}

void BellfruitGame::update(float dt)
{

	//m_currentScene->getFirstPlayerObject()->OnUpdate(dt); // call player 1 update
	
	m_currentScene->update(dt); // update current scene

}

void BellfruitGame::render()
{

	m_currentScene->render(m_playerCameraComponent); // render scene

}



BellfruitGame::~BellfruitGame()
{
	
	delete m_currentScene;
	m_currentScene = nullptr;
	delete m_playerCameraComponent;
	m_playerCameraComponent = nullptr;
	delete m_inputHandlerFirstObject;	

}