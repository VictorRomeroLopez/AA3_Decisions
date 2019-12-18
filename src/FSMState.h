#pragma once
#include "FSM.h"
#include "Agent.h"

class FSMState
{
public:
	virtual void Enter(Agent* agent, float dtime);
	virtual void Update(Agent* agent, float dtime);
	virtual void Exit(Agent* agent, float dtime);
};

