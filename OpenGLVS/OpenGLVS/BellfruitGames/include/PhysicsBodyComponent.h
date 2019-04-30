#pragma once

#include <iostream>
#include "Component.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "CommonInterfaces/CommonRigidBodyBase.h"

#include "PhysicsWorld.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Z 5

class PhysicsBodyComponent : public Component
{
private:

	btScalar m_mass = 0.0; // Object is only dynamic if this is not 0
	btScalar m_sphereRadius = 1.0f;
	btVector3 m_position;
	btVector3 m_scale;
	btVector3 m_collisionBoxSize;
	btQuaternion m_rotation;
	
	btCollisionShape* m_shape;
	
	std::string m_whatShape = "";

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

public:
	PhysicsWorld& physicsworld = physicsworld.getInstance();
	
	btDefaultMotionState* m_myMotionState;
	// ---------------- DEFAULT OBJECTS NEEDED ---------------------------------//
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	btTransform m_startTransform;

	// Default Constructor
	PhysicsBodyComponent() {};


	// Parameterized Constructor
	PhysicsBodyComponent(const btVector3 pos, const btQuaternion rot, btVector3 sca)
	{
		m_position = pos;
		m_startTransform = btTransform(btQuaternion(rot), btVector3(pos));

		// -> Create Rigid Body
		createRigidBody();
	};

	// Parameterized Constructor
	PhysicsBodyComponent(const btVector3 pos, const btQuaternion rot, btVector3 sca, btScalar mass, btVector3 colSize, std::string whatshape)
	{
		m_whatShape = whatshape;
		m_collisionBoxSize = colSize;
		m_position = pos;
		m_mass = mass;

		m_startTransform = btTransform(btQuaternion(rot), btVector3(pos));

		// -> Create Rigid Body
		createRigidBody();

	};


	// Parameterized Constructor
	PhysicsBodyComponent(const btVector3 pos, const btQuaternion rot, btVector3 sca, btScalar mass, btVector3 colSize, std::string whatshape, btScalar sphereColSize)
	{
		m_sphereRadius = sphereColSize;
		m_whatShape = whatshape;
		m_collisionBoxSize = colSize;
		m_position = pos;
		m_mass = mass;

		m_startTransform = btTransform(btQuaternion(rot), btVector3(pos));

		// -> Create Rigid Body
		createRigidBody();

	};
	void createRigidBody(); // Create Rigid Body
	// Component Interface functions
	void OnUpdate(float dt) { }

	void OnMessage(const std::string m) {

		btCollisionObject* l_collisionObjectPlayer = physicsworld.getDynamicsWorld()->getCollisionObjectArray()[physicsworld.getDynamicsWorld()->getNumCollisionObjects() - 1];
		btRigidBody* l_bodyPlayer = btRigidBody::upcast(l_collisionObjectPlayer);
		btQuaternion l_onKeyQuat;
		btTransform l_onKeyTransform;

		if (m == "moveLeft")
		{
			std::cout << "A: (Left) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(-10, 0, 0), btVector3(0, 0, 0));
		}

		else if (m == "moveRight")
		{
			std::cout << "D: (Right) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(10, 0, 0), btVector3(0, 0, 0));
		}

		else if (m == "moveForward")
		{
			std::cout << "W: (Forward) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(0, 0, -10), btVector3(0, 0, 0));
		}

		else if (m == "moveBackward")
		{
			std::cout << "S: (Backwards) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(0, 0, 10), btVector3(0, 0, 0));
		}


		else if (m == "speedBoost")
		{
			std::cout << "SPACE: (Booster) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(0, 0, -100), btVector3(0, 0, 0));
		}


		else if (m == "moveLeftArrow")
		{
			std::cout << "LeftArrow: (Left) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_onKeyQuat.setEuler(10.0, 0.0, 0.0);
			l_onKeyTransform.setRotation(l_onKeyQuat);
			l_bodyPlayer->setCenterOfMassTransform(l_onKeyTransform);
			//l_bodyPlayer->applyForce(btVector3(-10, 0, 0), btVector3(0, 0, 0));
		}

		else if (m == "moveRightArrow")
		{
			std::cout << "RightArrow: (Right) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(10, 0, 0), btVector3(0, 0, 0));
		}

		else if (m == "moveForwardArrow")
		{
			std::cout << "ForwardArrow: (Forward) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(0, 0, -10), btVector3(0, 0, 0));
		}

		else if (m == "moveBackwardArrow")
		{
			std::cout << "BackArrow: (Backwards) Pressed" << std::endl;
			l_bodyPlayer->activate(1);
			l_bodyPlayer->applyForce(btVector3(0, 0, 10), btVector3(0, 0, 0));
		}
	}

	

	btVector3* getPosition() { return &m_position; }
	btVector3* getScale() { return &m_scale; }
	btQuaternion* getRotation() { return &m_rotation; }

	void setPosition(btVector3 pos) { m_position = pos; }
	void setScale(btVector3 scale) { m_scale = scale; }
	void setRotation(btQuaternion ori) { m_rotation = ori; }

	~PhysicsBodyComponent();
};



inline void PhysicsBodyComponent::createRigidBody()
{
	if (m_whatShape == "btBoxShape")
	{
		// Collision Shape
		m_shape = new btBoxShape(m_collisionBoxSize);
		m_collisionShapes.push_back(m_shape);
		// Set rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (m_mass != 0.f);
		// Local Inertia
		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			m_shape->calculateLocalInertia(m_mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(m_startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_myMotionState, m_shape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setFriction(0.5);
		physicsworld.getDynamicsWorld()->addRigidBody(body);
	}
	else if (m_whatShape == "btSphereShape")
	{
		m_shape = new btSphereShape(m_sphereRadius);
		m_collisionShapes.push_back(m_shape);
		// Set rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (m_mass != 0.f);
		// Local Inertia
		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			m_shape->calculateLocalInertia(m_mass, localInertia);
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(m_startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_myMotionState, m_shape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setFriction(1.5);
		physicsworld.getDynamicsWorld()->addRigidBody(body);
	}	
}

// Clean up
inline PhysicsBodyComponent::~PhysicsBodyComponent()
{
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = physicsworld.getDynamicsWorld()->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = physicsworld.getDynamicsWorld()->getCollisionObjectArray()[i];

		btRigidBody* body = btRigidBody::upcast(obj);

		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		physicsworld.getDynamicsWorld()->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < m_collisionShapes.size(); j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		m_collisionShapes[j] = 0;
		delete shape;
	}

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	m_collisionShapes.clear();
}



