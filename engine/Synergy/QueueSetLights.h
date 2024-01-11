#pragma once
#include "QueueNode.h"
#include <vector>
class Light;

class QueueSetLights : public QueueNode
{
public:
	QueueSetLights(std::vector<Light*> lights);
	void Render(Renderer* renderer);
private:

	std::vector<Light*> _Lights;

};

