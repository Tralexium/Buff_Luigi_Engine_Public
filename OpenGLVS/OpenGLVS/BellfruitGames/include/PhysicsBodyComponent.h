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

#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Z 5




class PhysicsBodyComponent : public Component
{
private:

	btScalar m_mass = 0.0; // Object is only dynamic if this is not 0
	btVector3 m_position;
	btVector3 m_scale;
	btQuaternion m_rotation;
	//btVector3 m_collisionShapeSize = btVector3(10.0, 10.0, 10.0);

	
	//btTransform* m_currentTransform;

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
	
	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	
	btTransform m_startTransform;


	// Default Constructor
	PhysicsBodyComponent() {};

	// Parameterized Constructor
	PhysicsBodyComponent(const btVector3 pos,const btQuaternion rot, btVector3 sca, btScalar mass )
	{
		
	
		m_position = pos;
		m_mass = mass;


		m_startTransform = btTransform(btQuaternion(rot), btVector3(pos));
		

		// -> Create Rigid Body
		createRigidBody();
		
	};



	void createRigidBody(); // Create Rigid Body

	void step(); // Step the simulation

	// Component Interface functions
	virtual void OnUpdate(float dt) { };
	virtual void OnMessage(const std::string m) {};

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
	// Collision Shape
	boxShape = new btBoxShape(btVector3(btScalar(1.), btScalar(1.), btScalar(1.)));
	m_collisionShapes.push_back(boxShape);

	
	//btTransform groundTransform;
	// Create Dynamic Objects
	//groundTransform.setIdentity();
	


	// Set rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (m_mass != 0.f);

			
		
	// Local Inertia
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		boxShape->calculateLocalInertia(m_mass, localInertia);

	//groundTransform.setOrigin(m_startTransform.getOrigin());
	
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(m_startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_myMotionState, boxShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);

	//std::cout << m_startTransform.getOrigin() << std::endl;

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

