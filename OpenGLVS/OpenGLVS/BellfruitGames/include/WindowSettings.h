#pragma once
/*!
\file WindowSettings.h
*/

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

};