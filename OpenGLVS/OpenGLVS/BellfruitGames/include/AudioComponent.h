#pragma once
/*!
\file AudioComponent.h
*/
#include "Component.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include "fmod_common.h"

#include <iostream>

/*!
\class AudioComponent
\brief Handles the audio for the component.
*/
class AudioComponent : public Component
{
private:
	FMOD::System     *system;
	FMOD::Sound      *sound1, *sound2, *sound3;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;

public:


	//! Constructor
	/*!
	\param filepath filepath to the audio file.
	\brief initializes FMOD, creates a sound and sets mode to 2D
	*/
	AudioComponent(const char* filepath) {

		result = FMOD::System_Create(&system);

		result = system->getVersion(&version);

		if (version < FMOD_VERSION)
		{
			printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
		}

		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); // initialize fmod

		result = system->createSound(filepath, FMOD_DEFAULT, 0, &sound1); // createsound

		result = sound1->setMode(FMOD_2D); //setmode to 2D sound


		FMODErrorCheck(result);

	};


	//! Play Sound function
	/*!
	\brief This function will play the sound file we loaded in to sound1.
	*/
	void playSound() {

		result = system->playSound(sound1, 0, false, &channel); // play sound

		result = system->update(); // update sound
	}

	/*! Destructor
	\
	\
	*/
	~AudioComponent() {

		result = sound1->release(); // release memory
	};

	//! Error Check function
	/*!
	\brief This function will play the sound file we loaded in to sound1.
	*/
	void FMODErrorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
			exit(-1);
		}
	}


	//! Update Function.
	/*!
	\param dt
	*/
	void OnUpdate(float dt) override {

	}
	//! OnMessage Function.
	/*!
	\param m
	*/
	void OnMessage(const std::string m) override {


	}


};

