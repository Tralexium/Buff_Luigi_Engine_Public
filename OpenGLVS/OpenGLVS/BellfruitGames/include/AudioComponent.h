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
	FMOD::System     *system = 0; 
	FMOD::Sound      *sound1, *sound2, *sound3;
	FMOD::Channel    *channel = 0;
	FMOD::Reverb3D   *reverb = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;
	FMOD_VECTOR		 *pos;
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

		result = system->init(32, FMOD_INIT_3D_RIGHTHANDED, extradriverdata); //sets the coordinate system to right handed, same as opengl

		result = system->createSound(filepath, FMOD_3D_INVERSEROLLOFF, 0, &sound1); // createsound

		result = system->createReverb3D(&reverb); //Creates a 'virtual reverb' object

		if (version < FMOD_VERSION)
		{
			printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
		}

		FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
		result = reverb->setProperties(&prop2);

		pos = new FMOD_VECTOR{ posx, posy, posz };

		//std::cout << " Position: " << pos.x << pos.y << pos.z << std::endl;
		mindist = mindis;
		maxdist = maxdis;
		result = reverb->set3DAttributes(pos, mindist, maxdist);
		FMODErrorCheck(result);
		std::cout << "reverb; " << mindist << "    " << maxdist << std::endl;

		FMODErrorCheck(result);

	};


	//! Play Sound function
	/*!
	\brief This function will play the sound file we loaded in to sound1.
	*/
	void playSound() {

		result = system->playSound(sound1, 0, false, &channel); // play sound
		FMODErrorCheck(result);

		result = system->update(); // update sound
		FMODErrorCheck(result);
	}

	/*! Destructor
	\
	\
	*/
	~AudioComponent() {

		result = sound1->release(); // release memory
		FMODErrorCheck(result);

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
	void UpdatePosition(glm::vec3 position) {
		FMOD_VECTOR soundpos = { position.x, position.y, position.z };

		result = reverb->set3DAttributes(&soundpos, mindist, maxdist);
		FMODErrorCheck(result);

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
	void UpdateListener(glm::vec3 position, glm::vec3 forward, glm::vec3 up)  {
		FMOD_VECTOR listenerpos = { position.x, position.y, position.z };
		//FMOD_VECTOR listenerup = {0, 0, 0 };
		//glm::vec3 uForward = glm::sqrt(forward);
		FMOD_VECTOR listenerforward = { forward.x, forward.y, forward.z };
		FMOD_VECTOR listenerup = { up.x, up.y, up.z };

		std::cout << "Listener Position: " << listenerpos.x << " " << listenerpos.y << " " << listenerpos.z << std::endl;
		result = system->set3DListenerAttributes(0, &listenerpos, 0, &listenerforward, &listenerup);
		FMODErrorCheck(result);

		result = system->update(); // update sound
		FMODErrorCheck(result);

	}

};

