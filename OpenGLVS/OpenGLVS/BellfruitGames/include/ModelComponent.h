#pragma once
/*!
\file ModelComponent.h
*/
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"

/*!
\class ModelComponent
\brief Manages model data.
*/
class ModelComponent : public Component
{

private:
	Model * theModel; //!< Model pointer.	
public:

	ModelComponent() : theModel(nullptr) {}
	//! Constructor.
	/*!
	\param model* sets the model.
	*/
	ModelComponent(Model *model) { theModel = model; }

	//! Update Function override.
	/*!
	\param dt, float for delta time.
	*/
	void OnUpdate(float dt) override {}

	//! OnMessage Function Override.
	/*!
	\param m const string which takes a message from components.
	*/
	void OnMessage(const std::string m) override {}

	//! Model getter function.
	/*!
	\returns a pointer to the model.
	*/
	Model * getModel() { return theModel; }

};
