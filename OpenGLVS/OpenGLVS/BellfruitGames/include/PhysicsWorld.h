#pragma once
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "CommonInterfaces/CommonRigidBodyBase.h"

#include "PhysicsBodyComponent.h"

#include "DebugDrawPhysics.h"

class PhysicsWorld
{
private:
	// ---------------- DEFAULT OBJECTS NEEDED ---------------------------------//
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	DebugDrawPhysics* m_debugDraw;

public:


	btTransform m_transform;




	
	
	PhysicsWorld() {

		overlappingPairCache = new btDbvtBroadphase(); //btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		// ------------ Things needed for initialization -------------------------------------------------------------------------------------------------------------------------------------------------//
		collisionConfiguration = new btDefaultCollisionConfiguration(); //collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		dispatcher = new btCollisionDispatcher(collisionConfiguration); //use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)

		solver = new btSequentialImpulseConstraintSolver; //the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

		m_debugDraw = new DebugDrawPhysics();


		m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		//-- Set Gravity of dynamics world --//
		m_dynamicsWorld->setGravity(btVector3(0.0, -9-8, 0.0));

		m_dynamicsWorld->setDebugDrawer(m_debugDraw);

		m_dynamicsWorld->getDebugDrawer()->setDebugMode(2);

		

	};

	DebugDrawPhysics* getPhysicsWorldDebugDrawer() { return m_debugDraw; }

	void drawWorld() {
	
		
		m_dynamicsWorld->debugDrawWorld();
	}

	btDiscreteDynamicsWorld* getDynamicsWorld() {
		return m_dynamicsWorld;
	}

	//! Copy Constructor.
	/*!
	*/
	PhysicsWorld(PhysicsWorld const&) {};

	//! Operator Overloader.
	/*!
	\brief Blocks accidentally making new instances of this object.
	*/
	void operator=(PhysicsWorld const&);

	

	//! Constructor.
	/*!
	\brief Returns only one instance of this object.
	*/
	static PhysicsWorld& getInstance()
	{
		static PhysicsWorld instance; //!< Guaranteed to be destroyed.
								  //!< Instantiated on first use.
		return instance;
	}

	

	~PhysicsWorld() {
		delete m_dynamicsWorld;


		delete solver;

		//delete broadphase
		delete overlappingPairCache;

		//delete dispatcher
		delete dispatcher;

		delete collisionConfiguration;
	
	};


};

