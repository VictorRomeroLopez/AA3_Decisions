#include <queue>
#include <map>
#include "GOAPAstar.h"
#include <iostream>

GOAPAstar::GOAPAstar()
{
}

GOAPAstar::~GOAPAstar()
{
}

void GOAPAstar::GeneratePath(WSR* _start, WSR* _end, std::vector<GOAPAction> _actions)
{
	generatedPath.clear();
	std::map<WSR*, WSR*> cameFrom;
	std::map<GOAPAction*, GOAPAction*> cameFromAction;
	GOAPAction* currentAction = nullptr;
	std::map<WSR*, int> costSoFar;
	std::priority_queue<std::pair<int, WSR*>, std::vector<std::pair<int, WSR*>>, std::greater<std::pair<int, WSR*>>> priority_queue;
	WSR* currentNode = new WSR();
	WSR* nodesContainer;
	int newCost;
	int i;
	priority_queue.push({ 0, _start });
	costSoFar[_start] = 0;

	while (priority_queue.size() > 0) {
		currentNode = priority_queue.top().second;
		priority_queue.pop();

		if (currentNode->CompareStates(_end))
			break;

		for (i = 0; i < _actions.size(); i++)
		{
			if (_actions[i].getPreconditions()->CompareStates(currentNode)) {
				
				nodesContainer = new WSR(currentNode->getStates());

				nodesContainer->ApplyAction(_actions[i].getRepercusions());

				newCost = costSoFar[currentNode] + _actions[i].getCost();

				if (costSoFar.count(nodesContainer) == 0 || newCost < costSoFar[currentNode]) {
					costSoFar[currentNode] = newCost;
					priority_queue.push({ CalculateHeuristic(nodesContainer, _end) + newCost, nodesContainer });
					cameFromAction[currentAction] = &_actions[i];
					cameFrom[currentNode] = nodesContainer;
				}
			}
		}
	}
	
	std::cout << "Total nodes explorats:" << cameFrom.size() << std::endl;
	currentNode = _end;
	generatedPath.push_back(currentNode);
	while (currentNode != _start) {
		/*for (int state : currentNode->getStates())
			std::cout << state;
		std::cout << std::endl;*/
		currentNode = cameFrom[currentNode];
	}
}

int GOAPAstar::CalculateHeuristic(WSR* _wsr1, WSR* _wsr2)
{
	return 0;
}
