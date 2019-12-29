#include "FSM.h"
#include "FSMStateFlee.h"
#include "FSMStateWander.h"
#include "FSMStateChase.h"

void FSMStateChase::Enter(Agent* agent, float dtime)
{
	std::cout << "Enter Chase" << std::endl;
}

void FSMStateChase::Update(Agent* agent, float dtime)
{
	std::cout << "Chase" << std::endl;
	((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMFlee(), agent, dtime);
}

void FSMStateChase::Exit(Agent* agent, float dtime)
{
	std::cout << "Exit Chase" << std::endl;
}
