#pragma once
#include "FSMState"
#include "Agent.h"

class FSMStateFlee
{
public:
	void Enter(Agent* agent, float dtime);
	void Update(Agent* agent, float dtime);
	void Exit(Agent* agent, float dtime);
};

