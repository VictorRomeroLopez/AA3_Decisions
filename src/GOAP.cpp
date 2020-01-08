#include "GOAP.h"
#include "GOAPAction.h"
#include "WSR.h"
#include "GOAPAstar.h"

GOAP::GOAP()
{
	WSR* start = new WSR({
		WState::TRUE,//Agent viu
		WState::TRUE,//Agent te arma
		WState::TRUE,//Arma carregada
		WState::FALSE,//Agent te bomba
		WState::FALSE,//Enemic visible
		WState::FALSE,//Enemic alineat
		WState::FALSE,//Enemic aprop
		WState::TRUE,//Enemic viu
		});

	WSR* goal = new WSR({
		WState::TRUE,//Agent viu
		WState::DONTCARE,//Agent te arma
		WState::DONTCARE,//Arma carregada
		WState::DONTCARE,//Agent te bomba
		WState::DONTCARE,//Enemic visible
		WState::DONTCARE,//Enemic alineat
		WState::DONTCARE,//Enemic aprop
		WState::FALSE,//Enemic viu
		});

	std::vector<GOAPAction> actions;

	actions.push_back(
		GOAPAction(
			"FleeEnemy",

			new WSR({
				WState::TRUE,
				WState::DONTCARE,
				WState::FALSE,
				WState::FALSE,
				WState::TRUE,
				WState::DONTCARE,
				WState::TRUE,
				WState::TRUE }),

			new WSR({
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE,
				WState::DONTCARE }))
	);
	
	actions.push_back(
		GOAPAction(
			"ActivateBomb",

			new WSR({
				WState::TRUE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::TRUE,
				WState::TRUE,
				WState::DONTCARE,
				WState::TRUE,
				WState::TRUE }),

			new WSR({
				WState::FALSE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE }))
	);
	
	actions.push_back(
		GOAPAction(
			"Reload",

			new WSR({
				WState::TRUE,
				WState::TRUE,
				WState::FALSE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE }),

			new WSR({
				WState::DONTCARE,
				WState::DONTCARE,
				WState::TRUE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE }))
	);
	
	actions.push_back(
		GOAPAction(
			"Shoot",

			new WSR({
				WState::TRUE,
				WState::TRUE,
				WState::TRUE,
				WState::DONTCARE,
				WState::TRUE,
				WState::TRUE,
				WState::TRUE,
				WState::TRUE }),

			new WSR({
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE }))
	);
	
	actions.push_back(
		GOAPAction(
			"Aim",

			new WSR({
				WState::TRUE,
				WState::TRUE,
				WState::TRUE,
				WState::DONTCARE,
				WState::TRUE,
				WState::FALSE,
				WState::TRUE,
				WState::TRUE }),

			new WSR({
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::TRUE,
				WState::DONTCARE,
				WState::DONTCARE }))
	);

	actions.push_back(
		GOAPAction(
			"Explore",

			new WSR({ 
				WState::TRUE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::FALSE,
				WState::DONTCARE,
				WState::FALSE,
				WState::TRUE }),

			new WSR({ 
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::TRUE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE }))
	);

	actions.push_back(
		GOAPAction(
			"ChaseEnemy",

			new WSR({
				WState::TRUE,
				WState::TRUE,
				WState::TRUE,
				WState::DONTCARE,
				WState::TRUE,
				WState::DONTCARE,
				WState::FALSE,
				WState::TRUE }),

			new WSR({ 
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::DONTCARE,
				WState::TRUE,
				WState::DONTCARE }))
	);
	
	GOAPAstar goapAstar;
	goapAstar.GeneratePath(start, goal, actions);

}

GOAP::~GOAP()
{
}

void GOAP::Update()
{
}
