#pragma once
/*
\file AudioManager.h
*/
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "AudioComponent.h"
/*
\class AudioManager
\brief Handles Audio, creating and returning them !(UNUSED due to time constraints)!
*/
class AudioManager
{
private:
	std::string filePath = "res/audio/";	//!< filepath name
	std::map<std::string, AudioComponent* > myMapOfAudio;	//!< map of audio pointers

public:
	//! GetAudio Function
	/*!
	\brief creates models and stores them in a map, and gets them from there.
	\param name gets audio filename from map
	*/
	AudioComponent* getAudio(string name)
	{
		if (myMapOfAudio.find(name) != myMapOfAudio.end()) //already exists so return
		{
			return myMapOfAudio[name]; //returns audio
		}
		else // doesnt exist so make new then return
		{
			AudioComponent* audio = new AudioComponent(filePath + name);
			myMapOfAudio[name] = audio;
			return myMapOfAudio[name]; //returns audio
		}

	};


	//! AudioManager default constructor
	/*!
	*/
	~AudioManager()
	{
		for (std::map<std::string, AudioComponent* >::iterator Iter = myMapOfAudio.begin(); Iter != myMapOfAudio.end(); ++Iter)
		{
			delete (*Iter).second;
			(*Iter).second = nullptr;
			(Iter) = myMapOfAudio.erase(Iter);
		}
	}


};