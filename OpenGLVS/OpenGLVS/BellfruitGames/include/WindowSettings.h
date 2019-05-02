#pragma once
/*!
\file WindowSettings.h
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glad/glad.h>
#include <iostream>
#include <string>

// TODO this entire class since its fucked
using namespace std;

/*!
\class WindowSettings
\brief Singleton window class for all window settings, a solution for global access
*/
class WindowSettings
{
private:

	// Remember that higher resolution on window reduces framerate!

	/*float screenHeight = 768.0f;
	float screenWidth = 1366.0f;*/
	float screenHeight = 1080.0f;
	float screenWidth = 1920.0f;
	//float screenHeight = 600.0f;
	//float screenWidth = 800.0f;

	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	//! Default Constructor.
	/*!
	*/
	WindowSettings() {}

	//! Destructor.
	/*!
	*/
	~WindowSettings() {}

	//! Copy Constructor.
	/*!
	*/
	WindowSettings(WindowSettings const&);

	//! Operator Overloader.
	/*!
	\brief Blocks accidentally making new instances of this object.
	*/
	void operator=(WindowSettings const&);



public:

	//! Constructor.
	/*!
	\brief Returns only one instance of this object.
	*/
	static WindowSettings& getInstance()
	{
		static WindowSettings instance; //!< Guaranteed to be destroyed.
								  //!< Instantiated on first use.
		return instance;
	}

	float getScreenHeight() { return screenHeight; }

	float getScreenWidth() { return screenWidth; }

	float getNearPlane() { return nearPlane; }

	float getFarPlane() { return farPlane; }

	string GetOpenGLError()
	{
		// opengl doesn't report error conditions, you have
		// to ask for any errors - this will return
		// a string representing any open gl errors found
		// if all is ok you get the empty string

		string s = "";
		GLenum err;
		err = glGetError();

		if (err == GL_NO_ERROR)
		{
			return s;
		}

		DebugBreak();	//want to know about the error - set a breakpoint here while debugging

						// loop scanning for errors and appending them to a string
		while ((err != GL_NO_ERROR) && (s.length() < 128)) // stop infinite loop!!
		{
			switch (err)
			{
			case GL_NO_ERROR:
				//"No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
				break;

			case GL_INVALID_ENUM:
				s = s + "GL_INVALID_ENUM "; //"An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
				break;

			case GL_INVALID_VALUE:
				s = s + "GL_INVALID_VALUE "; //"A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
				break;

			case GL_INVALID_OPERATION:
				s = s + "GL_INVALID_OPERATION "; //"The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
				break;

				//case GL_INVALID_FRAMEBUFFER_OPERATION:
				//    s = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
				//    break;

			case GL_OUT_OF_MEMORY:
				s = s + "GL_OUT_OF_MEMORY "; //"There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
				break;

			case GL_STACK_UNDERFLOW:
				s = s + "GL_STACK_UNDERFLOW";	//"An attempt has been made to perform an operation that would cause an internal stack to underflow.";
				break;

			case GL_STACK_OVERFLOW:
				s = s + "GL_STACK_OVERFLOW"; //"An attempt has been made to perform an operation that would cause an internal stack to overflow.";
				break;
			}
			// get next error, if any
			err = glGetError();
		}
		// return the error messages as a single string
		return s;
	}

};