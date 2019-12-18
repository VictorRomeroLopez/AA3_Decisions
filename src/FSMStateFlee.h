#pragma once
#include "FSMState.h"
#include "Agent.h"

class FSMStateFlee : public FSMState
{
public:
	void Enter(Agent* agent, float dtime);
	void Update(Agent* agent, float dtime);
	void Exit(Agent* agent, float dtime);
};
