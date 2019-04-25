#include "EculidanMovementComponent.h"
#include <math.h>
#define PI 3.141592635

// Sets values of x and y for Pvector
void EculidanMovementComponent::SetMutator(float i, float o)
{
	x = i;
	y = o;
}

void EculidanMovementComponent::VectorIncrease(EculidanMovementComponent vector)
{
	x += vector.x;//Vector increases in the x axies.
	y += vector.y;//Vector increases in the y axies.
}

// Adds to a Pvector by a constant number
void EculidanMovementComponent::ScalarIncrease(float scale)
{
	x += scale;//Scale increases in the x axies.
	y += scale;//Scale increases in the y axies.
}

// Subtracts 2 vectors
void EculidanMovementComponent::SubVector(EculidanMovementComponent subvector)
{
	x -= subvector.x;//Subvector increases in the x axies.
	y -= subvector.y;//Subvector increases in the y axies.
}

// Subtracts two vectors and returns the difference as a vector
EculidanMovementComponent EculidanMovementComponent::subTwoVector(EculidanMovementComponent v, EculidanMovementComponent v2)
{
	EculidanMovementComponent tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.SetMutator(v.x, v.y);
	return tmp;
}


// Adds to a Pvector by a constant number
void EculidanMovementComponent::SubScalar(float Scaler)
{
	x -= Scaler;
	y -= Scaler;
}

// Multiplies 2 vectors
void EculidanMovementComponent::VectorMultiple(EculidanMovementComponent Vector)
{
	x *= Vector.x;
	y *= Vector.y;
}

// Adds to a Pvector by a constant number
void EculidanMovementComponent::ScalarMultiple(float Scaler)
{
	x *= Scaler;
	y *= Scaler;
}

// Divides 2 vectors
void EculidanMovementComponent::divVector(EculidanMovementComponent Vector)
{
	x /= Vector.x;
	y /= Vector.y;
}

// Adds to a Pvector by a constant number
void EculidanMovementComponent::divScalar(float Scaler)
{
	x /= Scaler;
	y /= Scaler;
}


void EculidanMovementComponent::MaxMagnitude(double max)
{
	double size = MagnitudeFunction();

	if (size > max) {
		SetMutator(x / size, y / size);
	}
}

// Calculates the distance between the first Pvector and second Pvector
float EculidanMovementComponent::DistanceFunction(EculidanMovementComponent v)
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy * dy);
	return dist;
}

// Calculates the dot product of a vector
float EculidanMovementComponent::DotProductFunction(EculidanMovementComponent v)
{
	float dot = x * v.x + y * v.y;
	return dot;
}

// Calculates magnitude of referenced object
float EculidanMovementComponent::MagnitudeFunction()
{

	return sqrt(x*x + y * y);
}

void EculidanMovementComponent::SetMagnitudeFunction(float x)
{
	NormalizeFunction();
	ScalarMultiple(x);
}

// Calculate the angle between Pvector 1 and Pvector 2
float EculidanMovementComponent::AngleBetweenFunction(EculidanMovementComponent v)
{
	if (x == 0 && y == 0) return 0.0f;
	if (v.x == 0 && v.y == 0) return 0.0f;

	double dot = x * v.x + y * v.y;
	double v1mag = sqrt(x * x + y * y);
	double v2mag = sqrt(v.x * v.x + v.y * v.y);
	double amt = dot / (v1mag * v2mag);
	if (amt <= -1) {
		return PI;
	}
	else if (amt >= 1) {
		return 0;
	}
	float tmp = acos(amt);
	return tmp;
}

// normalize divides x and y by magnitude if it has a magnitude.
void EculidanMovementComponent::NormalizeFunction()
{
	float m = MagnitudeFunction();

	if (m > 0) {
		SetMutator(x / m, y / m);
	}
	else {
		SetMutator(x, y);
	}
}

// Creates and returns a copy of the Pvector used as a parameter
EculidanMovementComponent EculidanMovementComponent::copy(EculidanMovementComponent v)
{
	EculidanMovementComponent copy(v.x, v.y);
	return copy;
}



