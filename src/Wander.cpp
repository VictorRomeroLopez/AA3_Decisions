#include "Wander.h"

#pragma region CONSTRUCTOR/DESTRUCTOR
Wander::Wander()
{
	_wanderAngle = 0;
	_targetAngle = 0;
	lastAngle = 0;
}

Wander::Wander(Agent *agent)
{
	_wanderAngle = 0;
	_targetAngle = 0;
	lastAngle = - agent->getOrientation();
}

Wander::~Wander()
{
}
#pragma endregion

float lerp(float a, float b, float f);

//Returns a random number between -1 and 1 inclusive
float Wander::RandomBinomial() 
{
	return(rand() / (float)(RAND_MAX)) - (rand() / (float)(RAND_MAX));
}


void Wander::UpdateWanderAngle(Agent *agent) 
{
	_wanderAngle += RandomBinomial() * _wanderMaxAngleChange;
	_targetAngle = lastAngle + _wanderAngle;
	lastAngle = _targetAngle;
}

void Wander::CalculateNewWanderPosition(Agent *agent) 
{
	agent->setCircleCenter(agent->getPosition() + (agent->getVelocity().Normalize() * _wanderOffset));
	agent->setTarget(Vector2D(
		agent->getCircleCenter().x + _wanderRadius * cos(_targetAngle),
		agent->getCircleCenter().y + _wanderRadius * sin(_targetAngle)
	));
}

void Wander::applySteeringForce(Agent *agent, float dtime)
{
	UpdateWanderAngle(agent);
	CalculateNewWanderPosition(agent);
	agent->getDesiredVelocity(desiredVelocity);
	agent->calculateSteeringForce(steeringForce, desiredVelocity);
	agent->UpdateForces(steeringForce, dtime);
}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
