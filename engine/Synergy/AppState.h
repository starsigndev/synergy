#pragma once

class SynUI;
class IMenuBar;

class AppState
{
public:

	AppState();
	virtual void InitState() {};
	virtual void UpdateState(float time_delta) {};
	virtual void RenderState() {};
	virtual void EndState() {};

protected:

	SynUI* _UI;
	IMenuBar* _MenuBar;

};

