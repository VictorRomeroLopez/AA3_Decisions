#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Graf.h"
#include "Grid.h"
#include "Node.h"

class Grid;
class FSM;
class FSMState;
class FSMStateChase;
class FSMStateFlee;
class FSMStateWander;
class DecisionMakingAlgorithm;

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};

	class PathfindingAlgorithm 
	{
	public:
		PathfindingAlgorithm() {};
		virtual ~PathfindingAlgorithm() {};
		virtual void GeneratePath(Graf graph, Vector2D startPosition, Vector2D targetPosition) {}; 
		virtual std::vector<Node> GetGeneratedPath() { return std::vector<Node>(); };
	};

private:
	SteeringBehavior *steering_behaviour;
	PathfindingAlgorithm* pathfinding_algorithm;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Vector2D vDelta;
	Vector2D circleCenter;
	float visionRadius;
	bool isZombie;
	Agent* agentTarget;
	
	DecisionMakingAlgorithm* brain;
	FSMStateChase* fsmStateChase;
	FSMStateFlee* fsmStateFlee;
	FSMStateWander* fsmStateWander;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	bool hasArrivedToTarget;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	Graf graph;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getVisionRadius();
	void setVisionRadius(float newRadius);
	void setIsZombie(bool isItZombie);
	Agent* getAgentTarget();
	void setAgentTarget(Agent* agentToTarget);
	FSMStateChase* getFSMChase();
	FSMStateFlee* getFSMFlee();
	FSMStateWander* getFSMWander();
	DecisionMakingAlgorithm* getDecisionMakingAlgorithm();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	bool GetHasArrivedToTarget();
	void SetHasArrivedToTarget(bool value);
	Agent::PathfindingAlgorithm* getAlgorithm();
	void setBehavior(SteeringBehavior *behavior);
	void setAlgorithm(PathfindingAlgorithm *algorithm);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void InitializeGraph(Grid* grid);
	Graf GetGraph();
	void SetDecisionMakingAlgorithm(DecisionMakingAlgorithm* _decisionMakingAlgorithm);

	void setCircleCenter(Vector2D circleCenter);
	float getOrientation();
	Vector2D getCircleCenter();
	void getDesiredVelocity(Vector2D& desiredVelocityOut, bool seek = true, float speedFactor = 1);
	void calculateSteeringForce(Vector2D& steeringForce, Vector2D desiredVelocity);
	void UpdateForces(Vector2D steeringForce, float dtime);
};
