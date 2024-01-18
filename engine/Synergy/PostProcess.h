#pragma once
#include <vector>

class RenderTarget2D;
class SmartDraw;
class Pipeline2D;

class PostProcess
{
public:

	PostProcess();
	void SetInput(RenderTarget2D* input);
	void CreateTargets(int width, int height, int num);
	void AddTarget(int width, int height);
	void BindTarget(int index);
	void ReleaseTarget(int index);
	RenderTarget2D* GetOutput();
	void Present(int index, Pipeline2D* pipeline = nullptr);
	void Present(RenderTarget2D* target,Pipeline2D* pipeline = nullptr);
	virtual void Process();
	RenderTarget2D* GetTarget(int index);


protected:

	RenderTarget2D* _Input;
	RenderTarget2D* _Output;
	std::vector<RenderTarget2D*> _Targets;
	SmartDraw* _Draw;


};


