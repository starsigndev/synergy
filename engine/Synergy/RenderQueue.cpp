#include "RenderQueue.h"

void RenderQueue::AddNode(QueueNode* node) {

	_Nodes.push_back(node);

}

int RenderQueue::NodeCount() {

	return _Nodes.size();

}

QueueNode* RenderQueue::GetNode(int index) {

	return _Nodes[index];

}

std::vector<QueueNode*> RenderQueue::GetNodes() {

	return _Nodes;

}
