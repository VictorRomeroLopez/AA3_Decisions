#pragma once
#include "vector"
#include "WSR.h"
#include "GOAPAction.h"

class GOAPAstar
{
private:
	std::vector<WSR*> generatedPath;

public:
	GOAPAstar();
	~GOAPAstar();
	void GeneratePath(WSR* _start, WSR* _end, std::vector<GOAPAction> _actions);
	int CalculateHeuristic(WSR* _wsr1, WSR* _wsr2);
};

