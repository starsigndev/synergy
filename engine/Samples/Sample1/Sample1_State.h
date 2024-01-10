#pragma once
#include "AppState.h"

class Texture2D;
class SmartDraw;

class Sample1_State : public AppState
{
public:

	void InitState();
	void UpdateState();
	void RenderState();

private:

	Texture2D* _tex1;
	SmartDraw* _draw;

};

