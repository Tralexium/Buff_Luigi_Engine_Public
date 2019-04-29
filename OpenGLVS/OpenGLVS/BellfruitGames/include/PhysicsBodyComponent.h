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
	btVector3 m_position;
	btVector3 m_scale;
	btVector3 m_collisionBoxSize;
	btQuaternion m_rotation;
	
	btCollisionShape* boxShape;

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
	PhysicsBodyComponent(const btVector3 pos, const btQuaternion rot, btVector3 sca, btScalar mass, btVector3 colSize)
	{

		m_collisionBoxSize = colSize;
		m_position = pos;
		m_mass = mass;

		m_startTransform = btTransform(btQuaternion(rot), btVector3(pos));

		// -> Create Rigid Body
		createRigidBody();

	};

	void createRigidBody(); // Create Rigid Body

	btVector3* getPosition() { return &m_position; }
	btVector3* getScale() { return &m_scale; }
	btQuaternion* getRotation() { return &m_rotation; }

	void setPosition(btVector3 pos) { m_position = pos; }
	void setScale(btVector3 scale) { m_scale = scale; }
	void setRotation(btQuaternion ori) { m_rotation = ori; }

	// Component Interface functions
	void OnUpdate(float dt) { }

	void OnMessage(const std::string m) {

		btCollisionObject* l_collisionObjectPlayer = physicsworld.getDynamicsWorld()->getCollisionObjectArray()[physicsworld.getDynamicsWorld()->getNumCollisionObjects() - 1];
		btRigidBody* l_bodyPlayer = btRigidBody::upcast(l_collisionObjectPlayer);

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
	}

	~PhysicsBodyComponent();
};



inline void PhysicsBodyComponent::createRigidBody()
{
	// Collision Shape
	boxShape = new btBoxShape(m_collisionBoxSize);
	m_collisionShapes.push_back(boxShape);

	// Set rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (m_mass != 0.f);

	// Local Inertia
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		boxShape->calculateLocalInertia(m_mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(m_startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_myMotionState, boxShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);

	physicsworld.getDynamicsWorld()->addRigidBody(body);
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



