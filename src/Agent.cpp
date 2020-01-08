#include "Agent.h"
#include "DecisionMakingAlgorithm.h"
#include "FSM.h"
#include "FSMState.h"
#include "FSMStateChase.h"
#include "FSMStateFlee.h"
#include "FSMStateWander.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             currentTargetIndex(-1),
				 mass(0.1f),
				 max_force(150),
				 max_velocity(200),
				 orientation(0),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false),
				 hasArrivedToTarget(true),
				 fsmStateChase(new FSMStateChase()),
				 fsmStateFlee(new FSMStateFlee()),
				 fsmStateWander(new FSMStateWander()),
				 visionRadius(200.f),
				 isZombie(false),
				 hasWeapon(false)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

void Agent::setAlgorithm(PathfindingAlgorithm* algorithm)
{
	pathfinding_algorithm = algorithm;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

void Agent::setMaxVelocity(int newMaxVelocity)
{
	max_velocity = newMaxVelocity;
}

float Agent::getVisionRadius()
{
	return visionRadius;
}

void Agent::setVisionRadius(float newRadius)
{
	visionRadius = newRadius;
}

void Agent::setIsZombie(bool isItZombie)
{
	isZombie = isItZombie;
}

bool Agent::getHasWeapon()
{
	return hasWeapon;
}

void Agent::setHasWeapon(bool doesHeHaveAWeapon)
{
	hasWeapon = doesHeHaveAWeapon;
}

Agent* Agent::getAgentTarget()
{
	return agentTarget;
}

void Agent::setAgentTarget(Agent* agentToTarget)
{
	agentTarget = agentToTarget;
}

DecisionMakingAlgorithm* Agent::getDecisionMakingAlgorithm()
{
	return brain;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

bool Agent::GetHasArrivedToTarget()
{
	return hasArrivedToTarget;
}

void Agent::SetHasArrivedToTarget(bool value)
{
	hasArrivedToTarget = value;
}

Agent::PathfindingAlgorithm* Agent::getAlgorithm()
{
	return pathfinding_algorithm;
}

FSMStateChase* Agent::getFSMChase() {
	return fsmStateChase;
}

FSMStateFlee* Agent::getFSMFlee() {
	return fsmStateFlee;
}

FSMStateWander* Agent::getFSMWander() {
	return fsmStateWander;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::update(float dtime, SDL_Event *event)
{
	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	if(isZombie)
		brain->Update(this, dtime);

	// Apply the steering behavior
	//steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}



void Agent::addPathPoint(Vector2D point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}

int Agent::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

int Agent::getPathSize()
{
	return path.points.size();
}

Vector2D Agent::getPathPoint(int idx)
{
	return path.points[idx];
}

void Agent::clearPath()
{
	setCurrentTargetIndex(-1);
	path.points.clear();
}

void Agent::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

void Agent::draw()
{
	// Path
	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, visionRadius, 255, 0, 0, 255);

	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void Agent::InitializeGraph(Grid* grid)
{
	Node node;
	Node* aux;
	for (int i = 0; i < grid->getNumCellX(); i++)
	{
		for (int j = 0; j < grid->getNumCellY(); j++)
		{
			if (grid->isValidCell(Vector2D(i, j)))
			{
				//Comprovar
				node = Node(Vector2D(i, j));
				aux = new Node();

				if (graph.CheckNode(Vector2D(i-1, j)))
				{
					aux = graph.GetNode(Vector2D(i - 1, j));
					Connexion conn(&node, aux);
					node.AddConnexion(conn);
					aux->AddConnexion(conn);
				}

				aux = new Node();

				if (graph.CheckNode(Vector2D(i, j - 1)))
				{
					aux = graph.GetNode(Vector2D(i, j - 1));
					Connexion conn(&node, aux);
					node.AddConnexion(conn);
					aux->AddConnexion(conn);
					//node.UpdateNode(aux)-> position = aux.position && connections = aux.connections;
				}

				graph.AddNode(node);
			}
		}
	}
}

Graf Agent::GetGraph()
{
	return graph;
}

void Agent::SetDecisionMakingAlgorithm(DecisionMakingAlgorithm* _decisionMakingAlgorithm) {
	brain = _decisionMakingAlgorithm;
}

void Agent::setCircleCenter(Vector2D circleCenter) {
	this->circleCenter = circleCenter;
}

float Agent::getOrientation() {
	return orientation;
}

Vector2D Agent::getCircleCenter() {
	return circleCenter;
}

void Agent::getDesiredVelocity(Vector2D& desiredVelocityOut, bool seek, float speedFactor) {
	if (seek)
		desiredVelocityOut = target - position;
	else
		desiredVelocityOut = position - target;
	desiredVelocityOut.Normalize();
	desiredVelocityOut *= max_velocity * speedFactor;
}

void Agent::calculateSteeringForce(Vector2D& steeringForce, Vector2D desiredVelocity)
{
	vDelta = desiredVelocity - velocity;
	vDelta /= max_velocity;

	steeringForce = vDelta * max_force;
}

void Agent::UpdateForces(Vector2D steeringForce, float dtime)
{
	velocity += (steeringForce / mass) * dtime;
	velocity.Truncate(max_velocity);
	position += velocity * dtime;
}


