#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "AiBirdBoidComponent.h"

// =====================================================//
// ======== AIBirdBoid Functions from Boid.h =========== //
// ===================================================== //
#define w_height window_height
#define w_width window_width
#define PI 3.141592635

AIBirdBoidComponent::AIBirdBoidComponent(float x, float y)
{
	BoidAcceleration = EculidanMovementComponent(0, 0);
	Boidvelocity = EculidanMovementComponent(rand() % 3 - 2, rand() % 3 - 2);
	Boidlocation = EculidanMovementComponent(x, y);
	BoidmaxSpeed = 3.5;
	BoidmaxForce = 0.5;
}


AIBirdBoidComponent::AIBirdBoidComponent(float x, float y, bool BirdPredCheck)
{
	Birdpredator = BirdPredCheck;
	if (BirdPredCheck == true) {
		BoidmaxSpeed = 7.5;
		BoidmaxForce = 0.5;
		Boidvelocity = EculidanMovementComponent(rand() % 3 - 1, rand() % 3 - 1);
	}
	else {
		BoidmaxSpeed = 3.5;
		BoidmaxForce = 0.5;
		Boidvelocity = EculidanMovementComponent(rand() % 3 - 2, rand() % 3 - 2);
	}
	BoidAcceleration = EculidanMovementComponent(0, 0);
	Boidlocation = EculidanMovementComponent(x, y);
}




void AIBirdBoidComponent::ApplyVectorAcceleration(EculidanMovementComponent Forces)
{
	BoidAcceleration.VectorIncrease(Forces);
}


//Three Laws 

// Separation
//The first law that i will be implementing for the boid is seperation.
EculidanMovementComponent AIBirdBoidComponent::BoidSeparation(vector<AIBirdBoidComponent> boids)
{

	float desiredseparation = 20;//Distance between the speration of boids.
	EculidanMovementComponent steer(0, 0);
	int count = 0;//Count 

	for (int i = 0; i < boids.size(); i++)//Check if the boids are not to close as thats the purpose of sepration.
	{

		float Distance = Boidlocation.DistanceFunction(boids[i].Boidlocation);//Calculate the difference of distance between the boids for seperation.

		if ((Distance > 0) && (Distance < desiredseparation))//If the boids are to close then this if function makes them move from each other. 
		{
			EculidanMovementComponent difference(0, 0);
			difference = difference.subTwoVector(Boidlocation, boids[i].Boidlocation);
			difference.NormalizeFunction();
			difference.divScalar(Distance);
			steer.VectorIncrease(difference);
			count++;
		}

		if ((Distance > 0) && (Distance < desiredseparation) && Birdpredator == true
			&& boids[i].Birdpredator == true) //If there are two predetors then they are gonna seperate from each other.
		{
			EculidanMovementComponent pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(Boidlocation, boids[i].Boidlocation);
			pred2pred.NormalizeFunction();
			pred2pred.divScalar(Distance);
			steer.VectorIncrease(pred2pred);
			count++;
		}
		//If are boid is not a predetor but a predtor is found then there will be a large separation.
		//As in real life a prey will always try to get away from a predetor.
		else if ((Distance > 0) && (Distance < desiredseparation + 70) && boids[i].Birdpredator == true) {
			EculidanMovementComponent predetor(0, 0);
			predetor = predetor.subTwoVector(Boidlocation, boids[i].Boidlocation);
			predetor.ScalarMultiple(900);
			steer.VectorIncrease(predetor);
			count++;
		}
	}

	if (count > 0)//Looking at accleration where in this if function i go over the accelertaion but looking at,
				  // how the forces and how the maginitude changes as more force happens.
		steer.divScalar((float)count);
	if (steer.MagnitudeFunction() > 0) {
		// Steering = Desired - Velocity
		steer.NormalizeFunction();
		steer.ScalarMultiple(BoidmaxSpeed);
		steer.SubVector(Boidvelocity);
		steer.MaxMagnitude(BoidmaxForce);
	}
	return steer;
}

// Alignment
//looking at the second law which is alignent, in the first if function i will be,
//going over the velocity of boids this is so i can, 
//sort at the allignment between the voids.

EculidanMovementComponent AIBirdBoidComponent::BoidAlignment(vector<AIBirdBoidComponent> Boids)
{
	float neighbordist = 50; // With this float i can input the field of vision.

	EculidanMovementComponent sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float Distance = Boidlocation.DistanceFunction(Boids[i].Boidlocation);
		if ((Distance > 0) && (Distance < neighbordist)) { // 0 < d < 50
			sum.VectorIncrease(Boids[i].Boidvelocity);
			count++;
		}
	}
	//Then looking at what happens when boids are to close each other, 
	//This is where the alignment comes in and what happens when two boids,
	//are close to each other.
	if (count > 0) {
		sum.divScalar((float)count);//The first sum is used using the average of velocity.
									//Which divides the sum by the number of boids which are close by.
		sum.NormalizeFunction();//fpr the second sum you need to turn the sum into a unit vector to get the second sum to work.
		sum.divScalar(BoidmaxSpeed);// Then for the third part of the sum you need to mutiply by boid max speed.

		EculidanMovementComponent steer;//Looking at steer you need to have it equal the desired which is the velocity.
		steer = steer.subTwoVector(sum, Boidvelocity);//What the sum is it equals desired which is also known as the average.
		steer.MaxMagnitude(BoidmaxForce);
		return steer;
	}
	else {
		EculidanMovementComponent temp(0, 0);
		return temp;
	}
}
// Cohesion
//Then the third law which is cohesion finds the average loction like the alignment, 
// Then the boids use the steering force of the cohesion which allows us to be able,
// To be able to have the boids move.

EculidanMovementComponent AIBirdBoidComponent::BoidCohesion(vector<AIBirdBoidComponent> Boids)
{
	float neighbordist = 50;
	EculidanMovementComponent sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float d = Boidlocation.DistanceFunction(Boids[i].Boidlocation);
		if ((d > 0) && (d < neighbordist)) {
			sum.VectorIncrease(Boids[i].Boidlocation);
			count++;
		}
	}
	if (count > 0) {
		sum.divScalar(count);
		return BoidSeek(sum);
	}
	else {
		EculidanMovementComponent temp(0, 0);
		return temp;
	}
}




//Looking at the constructor boid seek the puprpose of this constructor,
// Is to find the steering force which will be used for the boids.
// Then also looking at these constructors you are able to normilze the vectors,
//And limit the max speed of the boid.
EculidanMovementComponent AIBirdBoidComponent::BoidSeek(EculidanMovementComponent vector)
{
	EculidanMovementComponent desired;
	desired.SubVector(vector); //The purpose of the desired sub vector is to point to,
							   // The target this allows the function to normalize and scale the boid to the,
							   //Set maxium speed this is done using a vector.

	desired.NormalizeFunction();
	desired.ScalarMultiple(BoidmaxSpeed);//The equation for what steering is, equals desired,
										 //Minus the velocity to find the steering.

	BoidAcceleration.subTwoVector(desired, Boidvelocity);
	BoidAcceleration.MaxMagnitude(BoidmaxForce);//The purpose of the max force is to be able to set a limit this,
												//Allows the steering force to have a set into so it can't keep getting faster theres a limit.
	return BoidAcceleration;
}


//Looking at the update contsructor, this contsructor modies the values that we recive,
//From the three laws which were the velioicty thats needed the loction of the boid and
//Be able to configure the acceleration.

void AIBirdBoidComponent::Boidupdate()
{

	BoidAcceleration.divScalar(.4);// You have this function to make the slow down not be abrupt as you want it smooth.

	Boidvelocity.VectorIncrease(BoidAcceleration);// Uses the vector to update the velocity.

	Boidvelocity.MaxMagnitude(BoidmaxSpeed);//Limits the boids max speed.
	Boidlocation.VectorIncrease(Boidvelocity);

	BoidAcceleration.divScalar(0);//The int has been set to 0 for each cycle so when the cycle reaches 0 it resets.

}


// The run class runs the flocks for the boids, updates the three laws.

void AIBirdBoidComponent::Boidrun(vector <AIBirdBoidComponent> v)
{
	Boidflock(v);
	Boidupdate();

}

// Applies the three laws to the flock of boids
void AIBirdBoidComponent::Boidflock(vector<AIBirdBoidComponent> v)
{
	EculidanMovementComponent sep = BoidSeparation(v);
	EculidanMovementComponent ali = BoidAlignment(v);
	EculidanMovementComponent coh = BoidCohesion(v);
	// Arbitrarily weight these forces
	sep.ScalarMultiple(1.5);
	ali.ScalarMultiple(1.0); // Might need to alter weights for different characteristics
	coh.ScalarMultiple(1.0);
	// Add the force vectors to acceleration
	ApplyVectorAcceleration(sep);
	ApplyVectorAcceleration(ali);
	ApplyVectorAcceleration(coh);
}



//Looking at the angle consturctor you can that this uses dot product to calculate the angle,
// Of the velocity which adds the purpose to allow are ducj to rotate in that direction.
float AIBirdBoidComponent::angle(EculidanMovementComponent v)
{
	// uses the informationn from dot product.
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}



