#pragma once
#include "QueueNode.h"

class Entity;

class QueueRenderEntity : public QueueNode
{
public:

	QueueRenderEntity(Entity* entity) { _Entity = entity; };
	void Render(Renderer* renderer);
	void SetBasic(bool basic) {
		_BasicRender = true;
	}
	void SetEntity(Entity* entity) {
		_Entity = entity;
	}
	void Enable() {
		_Enabled = true;
	}
	void Disable() {
		_Enabled = false;
	}
private:

	bool _Enabled = true;
	bool _BasicRender = true;
	Entity* _Entity;

};

