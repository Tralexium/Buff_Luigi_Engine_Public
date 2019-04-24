#include "EculidanMovement.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

#ifndef AIBirdBoid_H_
#define AIBirdBoid_H_



class AIBirdBoid {
public:
	bool Birdpredator;
	EculidanMovement Boidlocation;// This vector allows me to find a boids location for the flock,
	EculidanMovement Boidvelocity;// This vector allows me to find a boids velocity for the flock,
	EculidanMovement BoidAcceleration;// This vector allows me to find a boids acceleration for the flock,
	float BoidmaxSpeed;//Allows me to be able to limit the max speed of the vector input.
	float BoidmaxForce;//This allows me to be agle to limit the max force you work this out by doing the equation force = mass * acceleration. 
	AIBirdBoid() {}
	AIBirdBoid(float x, float y);
	AIBirdBoid(float x, float y, bool predCheck);
	void ApplyVectorAcceleration(EculidanMovement force);//Name as what it does applies acceleration to the vector to allow it to have force.
	// Three Laws that boids follow
	EculidanMovement BoidSeparation(vector<AIBirdBoid> AIBirdBoids);//If the boids are near to each other a vector will be created to allow distance between the boids to stop them from becoming to close. 
	EculidanMovement BoidAlignment(vector<AIBirdBoid> AIBirdBoids);//Allows when mutiple boids are near each other to have them match there veloictys togther.
	EculidanMovement BoidCohesion(vector<AIBirdBoid> AIBirdBoids);//This allows the boid when finding other boids to find there centre of the mass.
	EculidanMovement BoidSeek(EculidanMovement v);
	void Boidrun(vector <AIBirdBoid> v);
	void Boidupdate();
	void Boidflock(vector <AIBirdBoid> v);
	
	float angle(EculidanMovement v);

};























#endif
