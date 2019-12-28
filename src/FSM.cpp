#include "FSM.h"
#include "FSMStateChase.h"
#include "FSMStateFlee.h"
#include "FSMStateWander.h"

FSM::FSM() : current_state(new FSMStateWander())
{
}

FSM::~FSM()
{
}

void FSM::Update(Agent* agent, float dtime)
{
	current_state->Update(agent, dtime);
}

void FSM::ChangeState(FSMState* new_state, Agent* agent, float dtime)
{
	current_state->Exit(agent, dtime);
	current_state = new_state;
	current_state->Enter(agent, dtime);
}
