#pragma once
#include "Agent.h"

class DecisionMakingAlgorithm
{
public:
	DecisionMakingAlgorithm() {};
	virtual ~DecisionMakingAlgorithm() {};
	virtual void Update(Agent* agent, float dtime) {};
};

