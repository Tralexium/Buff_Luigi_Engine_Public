#include "EculidanMovement.h"
#include <math.h>
#define PI 3.141592635

// Sets values of x and y for Pvector
void EculidanMovement::SetMutator(float i, float o)
{
	x = i;
	y = o;
}

void EculidanMovement::VectorIncrease(EculidanMovement vector)
{
	x += vector.x;//Vector increases in the x axies.
	y += vector.y;//Vector increases in the y axies.
}

// Adds to a Pvector by a constant number
void EculidanMovement::ScalarIncrease(float scale)
{
	x += scale;//Scale increases in the x axies.
	y += scale;//Scale increases in the y axies.
}

// Subtracts 2 vectors
void EculidanMovement::SubVector(EculidanMovement subvector)
{
	x -= subvector.x;//Subvector increases in the x axies.
	y -= subvector.y;//Subvector increases in the y axies.
}

// Subtracts two vectors and returns the difference as a vector
EculidanMovement EculidanMovement::subTwoVector(EculidanMovement v, EculidanMovement v2)
{
	EculidanMovement tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.SetMutator(v.x, v.y);
	return tmp;
}


// Adds to a Pvector by a constant number
void EculidanMovement::SubScalar(float Scaler)
{
	x -= Scaler;
	y -= Scaler;
}

// Multiplies 2 vectors
void EculidanMovement::VectorMultiple(EculidanMovement Vector)
{
	x *= Vector.x;
	y *= Vector.y;
}

// Adds to a Pvector by a constant number
void EculidanMovement::ScalarMultiple(float Scaler)
{
	x *= Scaler;
	y *= Scaler;
}

// Divides 2 vectors
void EculidanMovement::divVector(EculidanMovement Vector)
{
	x /= Vector.x;
	y /= Vector.y;
}

// Adds to a Pvector by a constant number
void EculidanMovement::divScalar(float Scaler)
{
	x /= Scaler;
	y /= Scaler;
}


void EculidanMovement::MaxMagnitude(double max)
{
    double size = MagnitudeFunction();

    if (size > max) {
		SetMutator(x / size, y / size);
    }
}

// Calculates the distance between the first Pvector and second Pvector
float EculidanMovement::DistanceFunction(EculidanMovement v)
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy * dy);
	return dist;
}

// Calculates the dot product of a vector
float EculidanMovement::DotProductFunction(EculidanMovement v)
{
	float dot = x * v.x + y * v.y;
	return dot;
}

// Calculates magnitude of referenced object
float EculidanMovement::MagnitudeFunction()
{

	return sqrt(x*x + y * y);
}

void EculidanMovement::SetMagnitudeFunction(float x)
{
	NormalizeFunction();
	ScalarMultiple(x);
}

// Calculate the angle between Pvector 1 and Pvector 2
float EculidanMovement::AngleBetweenFunction(EculidanMovement v)
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
void EculidanMovement::NormalizeFunction()
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
EculidanMovement EculidanMovement::copy(EculidanMovement v)
{
	EculidanMovement copy(v.x, v.y);
	return copy;
}



