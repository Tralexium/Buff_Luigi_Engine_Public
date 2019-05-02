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
	FMOD::Reverb3D   *reverb;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;

	float mindist;
	float maxdist;

public:


	//! Constructor
	/*!
	\param filepath filepath to the audio file.
	\brief initializes FMOD, creates a sound and sets mode to 2D
	*/
	AudioComponent(const char* filepath, float posx, float posy, float posz, float mindis, float maxdis) {

		result = FMOD::System_Create(&system);

		result = system->getVersion(&version);

		if (version < FMOD_VERSION)
		{
			printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
		}

		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); // initialize fmod
		result = system->init(32, FMOD_INIT_3D_RIGHTHANDED, extradriverdata); //sets the coordinate system to right handed, same as opengl
		result = system->createReverb3D(&reverb); //Creates a 'virtual reverb' object
		FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_GENERIC;
		reverb->setProperties(&prop2);

		FMOD_VECTOR pos = { posx, posy, posz };
		float mindist = mindis;
		float maxdist = maxdis;
		reverb->set3DAttributes(&pos, mindist, maxdist);

		result = system->createSound(filepath, FMOD_3D, 0, &sound1); // createsound
		result = sound1->setMode(FMOD_3D_INVERSEROLLOFF); //setmode to 2D sound
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

	//! UpdatePosition Function
	/*!
	\param pos position to update to
	\brief updates position that the sound is emitted from
	*/
	void UpdatePosition(glm::vec3 pos) {
		FMOD_VECTOR soundpos = { pos.x, pos.y, pos.z };

		reverb->set3DAttributes(&soundpos, mindist, maxdist);
	};


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

	//! UpdateListener
	/*!
	\param pos position of the listener, forward forward orientation of the listener
	\brief updates the listener position so that the 3D audio works correctly
	*/
	void UpdateListener(glm::vec3 pos, glm::vec3 forward)  {
		FMOD_VECTOR listenerpos = { pos.x, pos.y, pos.z };
		FMOD_VECTOR listenerup = {1, 1, 1 };
		FMOD_VECTOR listenerforward = { forward.x, forward.y, forward.z };

		std::cout << "Listener Position: " << pos.x << pos.y << pos.z << std::endl;
		system->set3DListenerAttributes(0, &listenerpos, 0, &listenerforward, 0);
		system->update(); // update sound
	}

};

