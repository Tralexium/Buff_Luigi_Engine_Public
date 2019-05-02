#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"

#include <iostream>
#include <type_traits>

//MouseSettings& g_mouse = g_mouse.getInstance();
//WindowSettings& g_window = g_window.getInstance();

inline glm::vec3 mouseToWorldPos(
	double mousex, double mousey, float screenwidth, float screenheight,
	glm::mat4 proj, glm::mat4 view, glm::mat4 model)
{

	double x = (2.0 * mousex) / screenwidth - 1.0f;
	double y = 1.0f - (2.0 * mousey) / screenheight;
	double z = 1.0f;
	glm::vec3 ray = vec3(x, y, z);

	// HOMOGENEOUS SPACE
	glm::vec4 screenPos = glm::vec4(ray.x, ray.y, -1.0f, 1.0f);

	// PROJECTION SPACE
	glm::vec3 ray_eye = inverse(proj) * screenPos;

	glm::mat4 ray_model = model;

	ray_eye = vec4(ray_eye.x,ray_eye.y, -1.0, 0.0);

	glm::vec3 ray_wor = glm::inverse(view*  ray_model) * glm::vec4(ray_eye.x, ray_eye.y, ray_eye.z, 0.0f);

	// don't forget to normalise the vector at some point
	ray_wor = glm::normalize(ray_wor);

	// WORLD POS AS VEC3
	return glm::vec3(ray_wor);

}

inline btVector3 glmVec3toBt(const glm::vec3& vec) 
{

	btVector3 btvec(vec.x, vec.y, vec.z);
	


	return btvec;
}


inline btQuaternion glmQuatToBt(const glm::quat& vec) {

	btQuaternion btvec(vec.w, vec.x, vec.y, vec.z  );

	return btvec;
}

inline glm::vec3 BtVec3toglm(btTransform* btvec)
{

	glm::vec3 vec(btvec->getOrigin().getX(), btvec->getOrigin().getY(), btvec->getOrigin().getZ());

	
	
	return vec;
}

inline glm::quat BtQuattoglm(btTransform* btvec)
{

	glm::quat vec(btvec->getRotation().getW(), btvec->getRotation().getX(), btvec->getRotation().getY(), btvec->getRotation().getZ());
	



	return vec;
}