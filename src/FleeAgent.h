#pragma once
#include "Agent.h"

class FleeAgent :
	public Agent::SteeringBehavior
{
public:
	FleeAgent();
	~FleeAgent();
	void applySteeringForce(Agent *agent, float dtime);
};
