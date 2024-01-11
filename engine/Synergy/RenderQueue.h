#pragma once
#include <vector>

class QueueNode;

class RenderQueue
{
public:

	//Nodes
	void AddNode(QueueNode* node);

	int NodeCount();
	QueueNode* GetNode(int index);
	std::vector<QueueNode*> GetNodes();

private:

	std::vector<QueueNode*> _Nodes;

};

