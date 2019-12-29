#include "FSM.h"
#include "FSMStateChase.h"
#include "FSMStateWander.h"

void FSMStateWander::Enter(Agent* agent, float dtime)
{
	std::cout << "Enter Wander" << std::endl;
}

void FSMStateWander::Update(Agent* agent, float dtime)
{
	std::cout << "Wander" << std::endl;
	((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMChase(), agent, dtime);
}

void FSMStateWander::Exit(Agent* agent, float dtime)
{
	std::cout << "Exit Wander" << std::endl;
}
