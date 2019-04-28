#pragma once




/*!
\file MouseSettings.h
*/

using namespace std;

/*!
\class MouseSettings
\brief Singleton patterned mouse setting class for global mouse settings
*/
class MouseSettings
{
private:


	//! Default Constructor.
	/*!
	*/
	MouseSettings() {}

	//! Destructor.
	/*!
	*/
	~MouseSettings() {}

	//! Copy Constructor.
	/*!
	*/
	MouseSettings(MouseSettings const&);

	//! Operator Overloader.
	/*!
	\brief Blocks accidentally making new instances of this object.
	*/
	void operator=(MouseSettings const&);



public:

	double m_currentMouseXpos;
	double m_currentMouseYpos;

	double m_previousMouseXpos;
	double m_previousMouseYpos;

	//! Constructor.
	/*!
	\brief Returns only one instance of this object.
	*/
	static MouseSettings& getInstance()
	{
		static MouseSettings instance; //!< Guaranteed to be destroyed.
								  //!< Instantiated on first use.
		return instance;
	}



	//void setCurrentMouseXpos(double currentXmousepos) { m_currentMouseXpos = currentXmousepos; }

	//void setCurrentMouseYpos(double currentYmousepos) { m_currentMouseYpos = currentYmousepos; }




};
