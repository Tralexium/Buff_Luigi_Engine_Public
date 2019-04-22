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