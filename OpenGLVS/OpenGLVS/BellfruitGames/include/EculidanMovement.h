#include <iostream>

using namespace std;

#ifndef EculidanMovement_H_
#define EculidanMovement_H_

class EculidanMovement {

public:
	float x;
	float y;

	//Constructors
	EculidanMovement() {}
	EculidanMovement(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}


	
	void SetMutator(float x, float y);
	void VectorIncrease(EculidanMovement v);
	void ScalarIncrease(float x);

	void SubVector(EculidanMovement v);
	EculidanMovement subTwoVector(EculidanMovement v, EculidanMovement v2);
	void SubScalar(float x);

	void VectorMultiple(EculidanMovement v);
	void ScalarMultiple(float x);

	void divVector(EculidanMovement v);
	void divScalar(float x);

	void MaxMagnitude(double max);

	//Calculating Functions
	float DistanceFunction(EculidanMovement v);
	float DotProductFunction(EculidanMovement v);
	float MagnitudeFunction();
	void  SetMagnitudeFunction(float x);
	float AngleBetweenFunction(EculidanMovement v);
	void  NormalizeFunction();

	EculidanMovement copy(EculidanMovement v);







};

#endif
