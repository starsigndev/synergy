#pragma once
#include <vector>
#include "NodeController.h"

class SynData;

class SynModule
{
public:

	virtual void InitModule() {};
	virtual void UpdateModule() {};
	virtual void EndModule() {};
	virtual void Play() {};
	virtual void Pause() {};
	virtual void Stop() {};

public:

	

};

