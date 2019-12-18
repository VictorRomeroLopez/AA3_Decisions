#pragma once
#include "DecisionMakingAlgorithm.h"

class FSMState;

class FSM 
	: public DecisionMakingAlgorithm
{
public:
	FSMState current_state;
	FSM();
	~FSM();
	void Update();
	void ChangeStated(FSMState* new_state);
};

