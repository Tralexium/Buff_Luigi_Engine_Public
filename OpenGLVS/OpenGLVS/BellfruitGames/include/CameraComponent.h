#pragma once
/*!
\file CameraComponent.h
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "WindowSettings.h"
#include "Component.h"
#include "WindowSettings.h"

#define ROTATION_VALUE 0.001

/*!
\class CameraComponent
\brief handles majority of the camera related functionality.
*/
class CameraComponent : public Component
{
private:
	glm::quat m_ori; //!< glm::quat Variable orientation, stores orientation.	
	glm::vec3 m_pos; //!< glm::vec3 position, stores position.
	float m_sensitivity;
public:
	WindowSettings& g_window = g_window.getInstance(); // Global instance

	float m_fov; //!< Float field of view variable.

	bool b_shader = true; //!< bool to swap shader 

	//! Virtual Update Function.
	/*!
	\brief inherited update function.
	\param dt, float for delta time.
	*/
	void OnUpdate(float dt) override {}

	//! Virtual Message Function.
	/*!
	\brief inherited update function.
	\param dt, float for delta time.
	*/
	void OnMessage(const std::string m) override {}

	//! Default Constructor.
	/*!
	*/
	CameraComponent() : m_pos(0), m_ori(1, 0, 0, 0), m_fov(45), m_sensitivity(1000.0f) {}
	//! Parameterized Constructor.
	/*!
	\param pos the position.
	*/
	CameraComponent(const glm::vec3& pos) : m_pos(pos), m_ori(1, 0, 0, 0), m_fov(45), m_sensitivity(1000.0f) {}
	//! Parameterized Constructor.
	/*!
	\param pos the position.
	*/
	CameraComponent(const glm::vec3& pos, const glm::quat& orient) : m_pos(pos), m_ori(orient), m_fov(45), m_sensitivity(1000.0f) {}

	//! lookAt Function.
	/*!
	\param target target to look at.
	*/
	void lookAt(const glm::vec3& target) { m_ori = (glm::toQuat(glm::lookAt(m_pos, target, glm::vec3(0, 1, 0)))); }

	//! Position getter.
	/*!
	\returns the position.
	*/
	const glm::vec3& getPos() const { return m_pos; }

	//! Orientation getter.
	/*!
	\returns m_ori.
	*/
	const glm::quat& getOri() const { return m_ori; }

	//! Position Setter Function
	/*!
	\brief Sets a new position for the camera.
	\param newPosition - The new position of the camera.
	*/
	void setPos(const glm::vec3 newPosition) { m_pos = newPosition; }

	//! Orientation Setter Function
	/*!
	\brief Sets a new orientation for the camera.
	\param newOrientation - The new orientation of the camera.
	*/
	void setOri(const glm::quat newOrientation) { m_ori = newOrientation; }

	//! View matrix Getter Function.
	/*!
	\returns view matrix.
	*/
	glm::mat4 getViewMatrix() const { return glm::translate(glm::mat4_cast(glm::inverse(m_ori)), m_pos); }

	//! View matrix Getter Function.
	/*!
	\returns view matrix.
	*/
	glm::mat4 getInvertedViewMatrix() const { return glm::translate(glm::mat4_cast(glm::inverse(m_ori)), -m_pos); }

	//! View matrix Getter Function.
	/*!
	\returns projection matrix.
	*/
	glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(m_fov), g_window.getScreenWidth() / g_window.getScreenHeight(), g_window.getNearPlane(), g_window.getFarPlane()); }

	//! FOV setter Function.
	/*!
	\param angle The new angle as a float
	*/
	void setFOV(float fov) { m_fov = fov; }

	//! Translate Function
	/*!
	\brief Translates the camera's position.
	\param &v - the vec3 travel amount.
	*/
	void translate(const glm::vec3 &v) { m_pos += v * m_ori; }

	//! Translate Function
	/*!
	\brief Translates the camera's position.
	\param x - the X axis travel amount.
	\param y - the Y axis travel amount.
	\param z - the Z axis travel amount.
	*/
	void translate(float x, float y, float z) { m_pos += glm::vec3(x, y, z) * m_ori; }

	/*!
	* \brief Rotate the camera by a certain amount.
	* \param angle - how far the camera should rotate.
	* \param &axis - in which axis the camera is rotating.
	*/
	void rotate(float angle, const glm::vec3 &axis) { m_ori *= glm::angleAxis(angle, axis * m_ori); }

	/*!
	* \brief Rotate the camera by a certain amount.
	* \param angle - how far the camera should rotate.
	* \param x - set this to 1 if rotating in the X axis.
	* \param y - set this to 1 if rotating in the Y axis.
	* \param z - set this to 1 if rotating in the Z axis.
	*/
	void rotate(float angle, float x, float y, float z) { m_ori *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_ori); }

	/*!
	* \brief Rotate the camera in the Y axis.
	* \param angle - how far the camera should rotate.
	*/
	void yaw(float angle) { rotate(angle / m_sensitivity, 0.0f, 1.0f, 0.0f); }
	/*!
	* \brief Rotate the camera in the X axis.
	* \param angle - how far the camera should rotate.
	*/
	void pitch(float angle) { rotate(angle / m_sensitivity, 1.0f, 0.0f, 0.0f); }
	/*!
	* \brief Rotate the camera in the Z axis.
	* \param angle - how far the camera should rotate.
	*/
	void roll(float angle) { rotate(angle / m_sensitivity, 0.0f, 0.0f, 1.0f); }

	//! Quaternion Calculation.
	/*!
	\brief Quaternion calculation onverted to euler, removed Z and back to quaternion.
	\param axis the axis calculated on.
	\param angle angle calculated about.
	*/
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
	\brief Performs quaternion rotation based on Z axis being constrained.
	\param pitch left and right rotations.
	\param yaw up and down rotations.
	*/
	void quaternionRotation(float pitch, float yaw)
	{
		m_ori = (glm::normalize(calculateQuaternion(glm::vec3(0.0f, 1.0f, 0.0f), yaw) * m_ori));
		m_ori = (m_ori * (glm::normalize(calculateQuaternion(glm::vec3(1.0f, 0.0f, 0.0f), pitch))));
	}

};