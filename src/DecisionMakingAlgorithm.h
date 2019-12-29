#pragma once
#include "Agent.h"

class DecisionMakingAlgorithm
{
public:
	DecisionMakingAlgorithm() {};
	DecisionMakingAlgorithm(Agent* agent) {};
	virtual ~DecisionMakingAlgorithm() {};
	virtual void Update(Agent* agent, float dtime) {};
};

