#pragma once
/*!
\file ModelManager.h
*/
#include <vector>
#include <map>
#include <iostream>
#include "Model.h"

/*!
\class ModelManager
\brief Handles Models, creating and returning them.
*/
class ModelManager
{
private:

	std::string filePath = "res/models/"; //!< filepath name.
	std::string fileName = ".obj"; //!< filename.
	std::map<std::string, Model* > myMapOfModels; //!<  map of model pointers.

public:
	
	//! GetModel Function.
	/*!
	\brief creates models and stores them in a map, and gets them from there.
	\param name gets model name from map.
	*/
	Model* getModel(string name) 
	{	
		if (myMapOfModels.find(name) != myMapOfModels.end()) // already exists so return
		{
			return myMapOfModels[name]; // returns model
		}
		else // doesnt exist so make new then return
		{
			Model* model = new Model(filePath + name + fileName);
			myMapOfModels[name] = model;
			return myMapOfModels[name]; // returns model, 	
		}
	}; 

	//! ModelManager default destructor.
	/*!
	*/
	~ModelManager() 
	{
		for (map<std::string, Model* >::iterator Iter = myMapOfModels.begin(); Iter != myMapOfModels.end(); ++Iter) // clean up map
		{
			delete (*Iter).second;
			(*Iter).second = nullptr;

			(Iter) = myMapOfModels.erase(Iter);
			
		}
	}

};
