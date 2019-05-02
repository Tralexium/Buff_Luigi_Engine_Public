#pragma once
/*!
\file GameObject.h
*/


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <cstdlib>
#include "Component.h"

#include "TransformComponent.h"


//#include "CameraComponent.h"
//#include "TransformComponent.h"


#define Deg2Rad 0.01745329252f
#define Rad2Deg 57.29577f

/*!
\class GameObject
\brief handles game objects and adding components to them.
*/
class GameObject : public Component
{
private:
	int counter = 1;



	float movement = 0.01f;//speed of cube
	std::unordered_map<std::type_index, Component*> m_components; //!< map of components.
	glm::vec3 relativePosition;

public:
	
	/*! Component Getter Function
	\brief retrieves a pointer to a component stored in a map by index.
	*/
	template <typename T>
	T* getComponent()
	{
		auto iter = m_components.find(typeid(T));
		if (iter != std::end(m_components))
		{
			return dynamic_cast<T*>(iter->second);  // return component 
		}
		return nullptr; //return nullptr if we don't have a component of that type	
	}

	/*! addComponent function
	\brief stores component inside the m_components map.
	*/
	template <typename T>
	void addComponent(T* comp)
	{
		m_components[typeid(T)] = comp; //! add the component to unoreder map with hash of its typeid
	}

	//! Update Function override.
	/*!
	\param dt, float for delta time.
	*/
	void OnUpdate(float dt)//GoalKeeper movement
	{


		TransformComponent* tc = getComponent<TransformComponent>(); // Local pointer variable

		tc->translate(movement, 0, 0);
		counter++;

		if (counter == 500)
		{
			movement = movement * -1;

			counter = 1;
		}
		/*else if (counter == 200)
		{
			tc->translate(movement, 1, 0);
		}
		else if (counter == 300)
		{
			tc->translate(movement, -1, 0);
		}*/

	}

	void OnUpdate2(float dt)//Spaceship Movement
	{


		TransformComponent* tc = getComponent<TransformComponent>(); // local pointer variable

		tc->translate(movement, 0, 0);
		counter++;

		if (counter == 1000)
		{
			movement = movement * -1;

			counter = 1;
		}

	}
	//! OnMessage Function Override.
	/*!
	\param m const string which takes a message from components.
	*/
	void OnMessage(const std::string m) {



	}


	//! Getter for Relative Position.
	/*!
	\brief might be needed in other functions.
	*/
	inline glm::vec3 getRelativePos() { return relativePosition; }
	
};

