#include "AIBirdBoidComponent.h"
#include "AIFlockcomponent.h"


// =============================================== //
// ======== AIFlock Functions from AIFlock.h ========= //
// =============================================== //
//Creating the flock functions so i can then move onto the boids which are going,
//to allow me to add those boid functions to my duck to allow it to move.


int AIFlockComponent::GetBirdSize()//Read from the header to get the size of the bird for the flocking.
{
	return BirdFlock.size();//Returns the size of the flocked bird.
}


void AIFlockComponent::AddAIBoid(AIBirdBoidComponent b)//This allows me to be able to add a boid to my flock 
{
	BirdFlock.push_back(b);//Pushes back the flock so the boid can link to the flock.
}


AIBirdBoidComponent AIFlockComponent::GetBirdBoid(int i)
{
	return BirdFlock[i];//This allows the flock to be able to acess the birds boid.
}


void AIFlockComponent::AIFlocking()
{
	for (int i = 0; i < BirdFlock.size(); i++)
		BirdFlock[i].Boidrun(BirdFlock);//Then runs thorugh the bird boid class to be able to,
}