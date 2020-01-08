#include "GOAPAction.h"

GOAPAction::GOAPAction()
{}

GOAPAction::GOAPAction(std::string _action, WSR* _precondition, WSR* _repercusion) :
	action(_action),
	preconditions(_precondition),
	repercusions(_repercusion),
	cost(0)
{}

GOAPAction::~GOAPAction()
{}

std::string GOAPAction::getAction()
{
	return action;
}

WSR* GOAPAction::getPreconditions()
{
	return preconditions;
}

WSR* GOAPAction::getRepercusions()
{
	return repercusions;
}

int GOAPAction::getCost()
{
	return cost;
}
