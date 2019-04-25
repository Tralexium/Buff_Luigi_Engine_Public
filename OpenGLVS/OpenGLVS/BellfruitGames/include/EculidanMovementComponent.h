#include <iostream>

using namespace std;

#ifndef EculidanMovement_H_
#define EculidanMovement_H_

class EculidanMovementComponent:Component {

public:
	float x;
	float y;

	//Constructors
	EculidanMovementComponent() {}
	EculidanMovementComponent(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}



	void SetMutator(float x, float y);
	void VectorIncrease(EculidanMovementComponent v);
	void ScalarIncrease(float x);

	void SubVector(EculidanMovementComponent v);
	EculidanMovementComponent subTwoVector(EculidanMovementComponent v, EculidanMovementComponent v2);
	void SubScalar(float x);

	void VectorMultiple(EculidanMovementComponent v);
	void ScalarMultiple(float x);

	void divVector(EculidanMovementComponent v);
	void divScalar(float x);

	void MaxMagnitude(double max);

	//Calculating Functions
	float DistanceFunction(EculidanMovementComponent v);
	float DotProductFunction(EculidanMovementComponent v);
	float MagnitudeFunction();
	void  SetMagnitudeFunction(float x);
	float AngleBetweenFunction(EculidanMovementComponent v);
	void  NormalizeFunction();

	EculidanMovementComponent copy(EculidanMovementComponent v);

	void OnUpdate(float dt) override
	{
	}


	void OnMessage(const std::string m) override
	{


	}





};

#endif
