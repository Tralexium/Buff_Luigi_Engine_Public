#include <iostream>
#include <vector>
#include "AiBirdBoid.h"

#ifndef AIFlock_H_//Helps with duplication so you do not end up adding in the same file and having two of them.

#define AIFlock_H_

class AIFlock {
public:
vector<AIBirdBoid> BirdFlock;//This vector is going to allow me to be able to add mutiple flock which were go going to add to the object.
AIFlock() {}
int GetBirdSize();//This int will get the size of the flocks that are needed for the boids.
AIBirdBoid GetBirdBoid(int i);
void AddAIBoid(AIBirdBoid b);
//void AIFlocking();
};
#endif//If you use a ifndef then you must end with endif to terminate the function.