#include "WSR.h"

WSR::WSR()
{
}

WSR::WSR(std::vector<WState> _states) : states(_states)
{
}

WSR::~WSR()
{
}

std::vector<WState> WSR::getStates()
{
	return states;
}

bool WSR::CompareStates(WSR* _wsr)
{
	for (int i = 0; i < states.size(); i++) {
		if (states[i] == WState::DONTCARE)
			continue;
		else if (_wsr->getStates()[i] != states[i]) {
			return false;
		}
	}
	return true;
}

void WSR::ApplyAction(WSR* action)
{
	for (int i = 0; i < action->getStates().size(); i++) {
		if (action->getStates()[i] == WState::DONTCARE)
			continue;
		states[i] = action->getStates()[i];
	}
}
