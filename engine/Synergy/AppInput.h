#pragma once
#include "glm/glm.hpp"

class AppInput
{
public:
	
	static glm::vec2 _MousePosition;
	static glm::vec2 _MouseDelta;
	static bool _KeyState[512];
	static bool _ButtonState[16];

};

