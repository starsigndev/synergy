#include "AppInput.h"

glm::vec2 AppInput::_MousePosition = glm::vec3(0, 0, 0);
glm::vec2 AppInput::_MouseDelta = glm::vec3(0, 0, 0);

bool AppInput::_KeyState[512];
bool AppInput::_ButtonState[16];