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
	//glm::mat4 viewProjectionInverse = inverse(MVP);

	


	glm::vec3 ray_wor = (inverse(view) * ray_model * glm::vec4(ray_eye.x, ray_eye.y, ray_eye.z, 0.0f));
	// don't forget to normalise the vector at some point
	ray_wor = glm::normalize(ray_wor);


	// WORLD POS
	//glm::vec4 worldPos = viewProjectionInverse * screenPos;

	// WORLD POS AS VEC3
	return glm::vec3(ray_wor);

	/*RESOLVED

	Here's how to do it exactly, step by step.

	0) Obtain your mouse coordinates within the client area

	1) Get your Projection matrix and View matrix if no Model matrix required.

	2) Multiply Projection * View

	3) Inverse the results of multiplication

	4) Construct a vector4 consisting of

	x = mouseposition.x within a range of window x - transform to values between - 1 and 1

	y = mouseposition.y within a range of window y - transform to values between - 1 and 1 - remember to invert mouseposition.y if needed

	z = the depth value(this can be obtained with glReadPixel) - you can manually go from - 1 to 1 (zNear, zFar)

	w = 1.0

	5) Multiply the vector by inversed matrix created before

	6) Divide result vector by it's w component after matrix multiplication ( perspective division )*/

}

inline btVector3 glmVec3toBt(const glm::vec3& vec) 
{

	btVector3 btvec(vec.x, vec.y, vec.z);
	


	return btvec;
}


inline btQuaternion glmQuatToBt(const glm::quat& vec) {

	btQuaternion btvec(vec.w, vec.x, vec.y, vec.z);

	return btvec;
}

inline glm::vec3 BtVec3toglm(btTransform* btvec)
{

	glm::vec3 vec(btvec->getOrigin().getX(), btvec->getOrigin().getY(), btvec->getOrigin().getZ());

	
	
	return vec;
}

inline glm::quat BtQuattoglm(btTransform* btvec)
{

	glm::quat vec(btvec->getRotation().getX(), btvec->getRotation().getY(), btvec->getRotation().getZ(), btvec->getRotation().getW());
	



	return vec;
}