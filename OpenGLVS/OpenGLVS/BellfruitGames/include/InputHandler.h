#pragma once
/*!
\file InputHandler.h
*/
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "GameObject.h"

#include "json/json.h"

/*!
\class InputCommand
\brief Input interface which handles execution of inputs.
*/
class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& object) = 0;

};

//--------------------- TRANSLATION COMMANDS ---------------------------//
/*!
\class TranslateLeftCommand
\brief Handles translation to the left.
*/
class TranslateLeftCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override
	{ 
		if (obj.getComponent<PhysicsBodyComponent>())
		{
			obj.getComponent<PhysicsBodyComponent>()->OnMessage("moveLeft");
		}
		
	}
};

/*!
\class TranslateRightCommand
\brief Handles translation to the right.
*/
class TranslateRightCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override 
	{
		if (obj.getComponent<PhysicsBodyComponent>())
		{
			obj.getComponent<PhysicsBodyComponent>()->OnMessage("moveRight");
		}
	}
};

/*!
\class TranslateForwardsCommand
\brief Handles translation forwards.
*/
class TranslateForwardsCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override 
	{
		if (obj.getComponent<PhysicsBodyComponent>())
		{
			obj.getComponent<PhysicsBodyComponent>()->OnMessage("moveForward");
		}
	}
};

/*!
\class TranslateBackwardsCommand
\brief Handles translation backwards.
*/
class TranslateBackwardsCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override 
	{
		if (obj.getComponent<PhysicsBodyComponent>())
		{
			obj.getComponent<PhysicsBodyComponent>()->OnMessage("moveBackward");
		}
	}
};


// WANG MEN UBUTTON
class MenuButton : public InputCommand
{
public:
	void execute(GameObject& obj) override
	{
		if (obj.getComponent<UIComponent>())
		{
			obj.getComponent<UIComponent>()->OnMessage("renderMenu");
		}
	}
};



class TranslateLeftArrowCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override { obj.OnMessage("moveLeftArrow"); }
};


class TranslateRightArrowCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override { obj.OnMessage("moveRightArrow"); }
};


class TranslateForwardsArrowCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override { obj.OnMessage("moveForwardArrow"); }
};

class TranslateBackwardsArrowCommand : public InputCommand
{
public:
	void execute(GameObject& obj) override { obj.OnMessage("moveBackwardArrow"); }
};






/*!
\class InputHandler
\brief communicates with game objects to execute tasks.
*/
struct InputHandler
{
	
	// ASCII Keys as ints, INSERT KEYS BELOW ---------------// // can add more keys under here
	int rotateKey, moveForwardKey, moveBackwardKey, moveLeftKey, moveRightkey,
		moveForwardArrowKey, moveBackwardArrowKey, moveLeftArrowKey, moveRightArrowKey, menuKey;
	// ASCII KEYS as ints, END HERE----------------------------------------------------------//
	bool readInputsFromConfig(std::string levelJSONFile)
	{
		std::fstream jsonData;
		Json::Value root;
		Json::Reader reader;
		jsonData.open(levelJSONFile.c_str());
		// check for errors
		if (!reader.parse(jsonData, root))
		{
			std::cout << "Failed to parse data from: "
				<< levelJSONFile
				<< reader.getFormattedErrorMessages();
			return false;
		}

		const Json::Value keyboardInput = root["KeyboardInputs"];


		// WASD keys
		int rotate = keyboardInput["Rotate"].asInt();
		rotateKey = rotate;

		int tforward = keyboardInput["TForward"].asInt();
		moveForwardKey = tforward;

		int tbackward = keyboardInput["TBackward"].asInt();
		moveBackwardKey = tbackward;

		int tleft = keyboardInput["TLeft"].asInt();
		moveLeftKey = tleft;

		int tright = keyboardInput["TRight"].asInt();
		moveRightkey = tright;

		int tmenu = keyboardInput["TMenu"].asInt();
		menuKey = tmenu;


		// Arrow keys
		int tforwardArrow = keyboardInput["tforwardArrow"].asInt();
		moveForwardArrowKey = tforwardArrow;

		int tbackwardArrow = keyboardInput["tbackwardArrow"].asInt();
		moveBackwardArrowKey = tbackwardArrow;

		int tleftArrow = keyboardInput["tleftArrow"].asInt();
		moveLeftArrowKey = tleftArrow;

		int trightArrow = keyboardInput["trightArrow"].asInt();
		moveRightArrowKey = trightArrow;

		return true;
	}

	GameObject* m_gameObject; //!< game object pointer.
	std::map<int, InputCommand*> m_controlMapping; //!< map of controls.

	//! Constructor
	/*!
	\brief responsible for creating new input commands.
	\param GameObject* obj
	*/
	InputHandler(GameObject* obj) : m_gameObject(obj)
	{	
		readInputsFromConfig("res/configs/keyconfig.json");

		m_controlMapping[moveForwardKey] = new TranslateForwardsCommand;
		m_controlMapping[moveBackwardKey] = new TranslateBackwardsCommand;
		m_controlMapping[moveLeftKey] = new TranslateLeftCommand;
		m_controlMapping[moveRightkey] = new TranslateRightCommand;

		m_controlMapping[menuKey] = new MenuButton;

		m_controlMapping[moveLeftArrowKey] = new TranslateLeftArrowCommand;
		m_controlMapping[moveRightArrowKey] = new TranslateRightArrowCommand;
		m_controlMapping[moveForwardArrowKey] = new TranslateForwardsArrowCommand;
		m_controlMapping[moveBackwardArrowKey] = new TranslateForwardsArrowCommand;
	}

	//! Handle Inputs Void Function.
	/*!
	\brief handles input for the map of keys.
	\param const std::vector<bool>& keybuffer
	*/
	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for (const auto& mapEntry : m_controlMapping)
		{
			if (keyBuffer[mapEntry.first])
			{				
				mapEntry.second->execute(*m_gameObject);			
			}
		}

	}

	//! Destructor.
	/*!
	*/
	~InputHandler() {
		
		delete m_controlMapping[rotateKey];
		m_controlMapping[rotateKey] = nullptr;
		delete m_controlMapping[moveForwardKey];
		m_controlMapping[moveForwardKey] = nullptr;
		delete m_controlMapping[moveBackwardKey];
		m_controlMapping[moveBackwardKey] = nullptr;
		delete m_controlMapping[moveLeftKey];
		m_controlMapping[moveLeftKey] = nullptr;
		delete m_controlMapping[moveRightkey];
		m_controlMapping[moveRightkey] = nullptr;

		delete m_controlMapping[menuKey];
		m_controlMapping[menuKey] = nullptr;

		delete m_controlMapping[moveLeftArrowKey];
		m_controlMapping[moveLeftArrowKey] = nullptr;
		delete m_controlMapping[moveRightArrowKey];
		m_controlMapping[moveRightArrowKey] = nullptr;
		delete m_controlMapping[moveForwardArrowKey];
		m_controlMapping[moveForwardArrowKey] = nullptr;
		delete m_controlMapping[moveBackwardArrowKey];
		m_controlMapping[moveBackwardArrowKey] = nullptr;
	}

};