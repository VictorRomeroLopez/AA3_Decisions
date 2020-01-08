#pragma once
#include "Agent.h"

class SeekAgent :
	public Agent::SteeringBehavior
{
public:
	SeekAgent();
	~SeekAgent();
	void applySteeringForce(Agent *agent, float dtime);
};
