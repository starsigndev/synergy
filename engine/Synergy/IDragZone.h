#pragma once
#include "IControl.h"
class IDragZone : public IControl
{
public:
	IDragZone();
	void OnMouseDrag(glm::vec2 pos, glm::vec2 delta);
private:
};

