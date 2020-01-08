#pragma once
#include "vector"
#include "GOAPAction.h"

enum WState {
	TRUE,
	FALSE,
	DONTCARE
};

class WSR
{
private:
	std::vector<WState> states;

public:
	WSR();
	WSR(std::vector<WState> _states);
	~WSR();

	std::vector<WState> getStates();

	bool CompareStates(WSR* _wsr);
	void ApplyAction(WSR* action);
};

