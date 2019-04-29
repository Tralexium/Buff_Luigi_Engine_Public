#pragma once
/*!
\file Component.h
*/
#include <string>

/*!
\class Component
\brief An interface which enforces update and message function to all its sub classes.
*/
class Component
{
public:
	//! Pure Virutal Update Function.
	/*!
	\param dt
	*/
	virtual void OnUpdate(float dt) = 0;

	//! Pure Virtual OnMessage Function.
	/*!
	\param m
	*/
	virtual void OnMessage(const std::string m) = 0;

};

