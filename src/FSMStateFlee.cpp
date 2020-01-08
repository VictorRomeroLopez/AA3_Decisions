#include "FleeAgent.h"
#include "FSM.h"
#include "FSMStateFlee.h"
#include "FSMStateChase.h"
#include "FSMStateWander.h"

void FSMStateFlee::Enter(Agent* agent, float dtime)
{
	agent->setBehavior(new FleeAgent());
}

void FSMStateFlee::Update(Agent* agent, float dtime)
{
	if (Vector2D::Distance(agent->getPosition(), agent->getAgentTarget()->getPosition()) > agent->getVisionRadius())
		((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMWander(), agent, dtime);

	if (!agent->getAgentTarget()->getHasWeapon())
		((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMChase(), agent, dtime);
}

void FSMStateFlee::Exit(Agent* agent, float dtime)
{
}
