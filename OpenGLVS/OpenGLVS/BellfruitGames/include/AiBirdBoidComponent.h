#include "Component.h"
#include <iostream>

#include "EculidanMovementComponent.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

#ifndef AIBirdBoid_H_
#define AIBirdBoid_H_



class AIBirdBoidComponent : public Component {
public:
	bool Birdpredator;
	EculidanMovementComponent Boidlocation;// This vector allows me to find a boids location for the flock,
	EculidanMovementComponent Boidvelocity;// This vector allows me to find a boids velocity for the flock,
	EculidanMovementComponent BoidAcceleration;// This vector allows me to find a boids acceleration for the flock,
	float BoidmaxSpeed;//Allows me to be able to limit the max speed of the vector input.
	float BoidmaxForce;//This allows me to be agle to limit the max force you work this out by doing the equation force = mass * acceleration. 
	AIBirdBoidComponent() {}
	AIBirdBoidComponent(float x, float y);
	AIBirdBoidComponent(float x, float y, bool predCheck);
	void ApplyVectorAcceleration(EculidanMovementComponent force);//Name as what it does applies acceleration to the vector to allow it to have force.
														 // Three Laws that boids follow
	EculidanMovementComponent BoidSeparation(vector<AIBirdBoidComponent> AIBirdBoids);//If the boids are near to each other a vector will be created to allow distance between the boids to stop them from becoming to close. 
	EculidanMovementComponent BoidAlignment(vector<AIBirdBoidComponent> AIBirdBoids);//Allows when mutiple boids are near each other to have them match there veloictys togther.
	EculidanMovementComponent BoidCohesion(vector<AIBirdBoidComponent> AIBirdBoids);//This allows the boid when finding other boids to find there centre of the mass.
	EculidanMovementComponent BoidSeek(EculidanMovementComponent v);
	void Boidrun(vector <AIBirdBoidComponent> v);
	void Boidupdate();
	void Boidflock(vector <AIBirdBoidComponent> v);

	float angle(EculidanMovementComponent v);
	void OnUpdate(float dt) override
	{
	}


	void OnMessage(const std::string m) override
	{


	}

};
#endif









