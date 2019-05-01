#pragma once
/*!
\file BellfruitGame.h
*/


#include "Scene.h"

#include "CameraComponent.h"
#include "InputHandler.h"

/*!
\class BellfruitGame
\brief Manages and generates all game related data.
*/
class BellfruitGame 
{
private:

	Scene* m_currentScene; //!< current scene pointer.
	
	CameraComponent* m_playerCameraComponent; //!< camera component pointer.
	InputHandler* m_playerInputHandler;
	InputHandler* m_inputHandlerFirstObject; //!< Inputhandler pointer for first reel.

public:
	

	//! BellfruitGame default constructor.
	/*!
	*/
	BellfruitGame();


	//! BellfruitGame Destructor.
	/*!
	*/
	~BellfruitGame();

	//! Update function.
	/*!
	\brief updates game logic.
	*/
	void update(float dt);
	//! Render function.
	/*!
	\brief renders things to screen.
	*/
	void render();
	
	//! Getter function for first reel.
	/*!
	\brief gets the pointer to the first reel.
	*/
	InputHandler* getPlayerInputHandler() { return m_playerInputHandler; }
	
	//! Getter function for first reel.
	/*!
	\brief gets the pointer to the first reel.
	*/
	InputHandler* getInputHandlerFirstObject() { return m_inputHandlerFirstObject; }

	//! Getter function for the scene.
	/*!
	\brief gets the pointer to the current scene.
	*/
	Scene* getcurrentScene() { return m_currentScene; }
};