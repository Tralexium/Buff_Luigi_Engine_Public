#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/mat4x4.hpp>



#define MOVE_SPEED 0.1f
//#define MOVE_SPEED 0.003f // this speed for release
/*!
* \brief This component is responsible for controling the assosiated object.
*/
class TransformComponent : public Component
{
private:
	glm::vec3 m_pos; //!< stores the object position.
	glm::vec3 m_sca; //!< stores the object scale.
	glm::quat m_ori; //!< stores the object orientation.
	
public:
	
	/*!
	* \brief Inherited update function.
	* \param dt - delta time(framerate).
	*/
	void OnUpdate(float dt) override {}

	/*!
	* \brief Inherited message listener function.
	* \details Current functionality ranges from Rotation, Transformation and Scaling.
	* Feel free to expand this to your desires.
	* \param m - a string message that tells the object/component what to do.
	*/
	void OnMessage(const std::string m) override{}

	/*!
	* \brief Default constructor.
	*/
	TransformComponent() : m_pos(0), m_ori(1, 0, 0, 0), m_sca(1.0f) {}
	/*!
	* \brief A constructor that takes object position.
	* \param &pos - initial position of the object.
	*/
	TransformComponent(const glm::vec3& pos) : m_pos(pos), m_ori(1, 0, 0, 0), m_sca(1.0f) {}
	/*!
	* \brief A constructor that takes object position and orientation.
	* \param &pos - initial position of the object.
	* \param &orient - initial orientation of the object.
	*/
	TransformComponent(const glm::vec3& pos, const glm::quat& orient) : m_pos(pos), m_ori(orient), m_sca(1.0f) {}
	/*!
	* \brief A constructor that takes object position, orientation and scale.
	* \param &pos - initial position of the object.
	* \param &orient - initial orientation of the object.
	* \param &scale - initial scale of the object.
	*/
	TransformComponent(const glm::vec3& pos, const glm::quat& orient, const glm::vec3& scale) : m_pos(pos), m_ori(orient), m_sca(scale) {}

	/*! *\brief Returns the current position of the object. */
	const glm::vec3& getPosition() const { return m_pos; }
	/*! *\brief Returns the current orientation of the object. */
	const glm::quat& getOrientation() const { return m_ori; }
	/*! *\brief Returns the current scale of the object. */
	const glm::vec3& getScale() const { return m_sca; }
	

	
	/*!
	* \brief Sets a new position for the camera.
	* \param newPosition - The new position of the camera.
	*/
	void setPos(const glm::vec3 newPosition) { m_pos = newPosition; }

	/*!
	* \brief Sets a new orientation for the camera.
	* \param newOrientation - The new orientation of the camera.
	*/
	void setOri(const glm::quat newOrientation) { m_ori = newOrientation; }

	//! View matrix Getter Function.
	/*!
	\returns viewmatrix.
	*/
	glm::mat4 getViewMatrix() { return glm::translate(glm::mat4_cast(glm::inverse(m_ori)), -m_pos); }


	glm::quat calculateQuaternion(glm::vec3 axis, float angle) {
		glm::quat rotation;

		rotation.w = cos(angle / 2);
		rotation.x = sin(angle / 2) * axis.x;
		rotation.y = sin(angle / 2) * axis.y;
		rotation.z = 0;

		return rotation;
	}


	//! QuatCameraRotation.
	/*!
	\brief does a quaternion rotation.
	\param yaw up and down rotations.
	*/
	void quaternionRotation(float pitch, float yaw)
	{
		m_ori = (glm::normalize(calculateQuaternion(glm::vec3(0.0f, 1.0f, 0.0f), yaw) * m_ori));
		m_ori = (m_ori * (glm::normalize(calculateQuaternion(glm::vec3(1.0f, 0.0f, 0.0f), pitch))));
	}
	
	//! Translate Function.
	/*!
	translation in a vec3 axis, x,y,z
	\param v
	*/
	void translate(const glm::vec3 &v) { m_pos += v; }
	void translate(float x, float y, float z) { m_pos += glm::vec3(x, y, z) * m_ori; }

	/*! *\brief Returns the current view matrix. */
	glm::mat4 getModelMatrix()
	{
		glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), m_pos);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_sca);
		glm::mat4 rotationMatrix = glm::mat4_cast(m_ori);
		return transMatrix * rotationMatrix * scaleMatrix;
	}


	/*!
	* \brief Returns the euler angles of the assosiated object.
	*/
	glm::vec3 getEulerAngles()
	{
		return glm::eulerAngles(m_ori); //pitch yaw roll
	}

};
