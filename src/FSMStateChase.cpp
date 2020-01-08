#include "FSM.h"
#include "SeekAgent.h"
#include "FSMStateFlee.h"
#include "FSMStateWander.h"
#include "FSMStateChase.h"

void FSMStateChase::Enter(Agent* agent, float dtime)
{
	agent->setBehavior(new SeekAgent());
}

void FSMStateChase::Update(Agent* agent, float dtime)
{
	if (Vector2D::Distance(agent->getPosition(), agent->getAgentTarget()->getPosition()) > agent->getVisionRadius())
		((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMWander(), agent, dtime);
	
	if (agent->getAgentTarget()->getHasWeapon())
		((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMFlee(), agent, dtime);
}

void FSMStateChase::Exit(Agent* agent, float dtime)
{
}
