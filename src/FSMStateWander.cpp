#include "FSM.h"
#include "Wander.h"
#include "FSMStateChase.h"
#include "FSMStateWander.h"

void FSMStateWander::Enter(Agent* agent, float dtime)
{
	agent->setBehavior(new Wander());
}

void FSMStateWander::Update(Agent* agent, float dtime)
{
	if (Vector2D::Distance(agent->getPosition(), agent->getAgentTarget()->getPosition()) < agent->getVisionRadius()) {
		((FSM*)agent->getDecisionMakingAlgorithm())->ChangeState(agent->getFSMChase(), agent, dtime);
	}
}

void FSMStateWander::Exit(Agent* agent, float dtime)
{
}
