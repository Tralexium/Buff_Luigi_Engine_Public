#include <iostream>
#include <vector>
#include "AIBirdBoidComponent.h"
#include "Component.h"
#ifndef AIFlock_H_//Helps with duplication so you do not end up adding in the same file and having two of them.

#define AIFlock_H_

class AIFlockComponent :Component {
public:
	vector<AIBirdBoidComponent> BirdFlock;//This vector is going to allow me to be able to add mutiple flock which were go going to add to the object.
	AIFlockComponent() {}
	int GetBirdSize();//This int will get the size of the flocks that are needed for the boids.
	AIBirdBoidComponent GetBirdBoid(int i);
	void AddAIBoid(AIBirdBoidComponent b);
	//void AIFlocking();

	void OnUpdate(float dt) override
	{
	}


	void OnMessage(const std::string m) override
	{


	}
};
#endif//If you use a ifndef then you must end with endif to terminate the function.