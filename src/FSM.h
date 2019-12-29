#pragma once
#include "DecisionMakingAlgorithm.h"
#include "FSMState.h"

class FSM 
	: public DecisionMakingAlgorithm
{
public:
	FSMState* current_state;
	FSM();
	FSM(Agent* agent);
	~FSM();
	void Update(Agent* agent, float dtime);
	void ChangeState(FSMState* new_state, Agent* agent, float dtime);
};

