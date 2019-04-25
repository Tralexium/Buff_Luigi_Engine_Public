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


EculidanMovementComponent EculidanMovementComponent::subTwoVector(EculidanMovementComponent v, EculidanMovementComponent v2)
{
	EculidanMovementComponent tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.SetMutator(v.x, v.y);
	return tmp;
}


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

float EculidanMovementComponent::DistanceFunction(EculidanMovementComponent v)
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy * dy);
	return dist;
}


float EculidanMovementComponent::DotProductFunction(EculidanMovementComponent v)
{
	float dot = x * v.x + y * v.y;
	return dot;
}

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


EculidanMovementComponent EculidanMovementComponent::copy(EculidanMovementComponent v)
{
	EculidanMovementComponent copy(v.x, v.y);
	return copy;
}



