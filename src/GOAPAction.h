#pragma once
#include "string"

class WSR;

class GOAPAction {
private:
	std::string action;
	WSR* preconditions;
	WSR* repercusions;
	int cost;

public:
	GOAPAction();
	GOAPAction(std::string _action, WSR* _precondition, WSR* _repercusion);
	~GOAPAction();
	std::string getAction();
	WSR* getPreconditions();
	WSR* getRepercusions();
	int getCost();
};

