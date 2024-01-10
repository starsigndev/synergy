#pragma once
class AppState
{
public:

	virtual void InitState() {};
	virtual void UpdateState(float time_delta) {};
	virtual void RenderState() {};
	virtual void EndState() {};

private:

};

