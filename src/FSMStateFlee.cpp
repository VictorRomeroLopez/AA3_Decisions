#include "FSMStateFlee.h"

void FSMStateFlee::Enter(Agent* agent, float dtime)
{
	std::cout << "Enter Flee" << std::endl;
}

void FSMStateFlee::Update(Agent* agent, float dtime)
{
	std::cout << "Flee" << std::endl;
}

void FSMStateFlee::Exit(Agent* agent, float dtime)
{
	std::cout << "Exit Flee" << std::endl;
}
