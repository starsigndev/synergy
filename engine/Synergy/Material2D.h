#pragma once

#include "MaterialBase.h"

class Material2D : public MaterialBase
{
public:
	Material2D();

	void Bind(bool second_pass);

};

