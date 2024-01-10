#include "Sample1_State.h"
#include <iostream>
#include "Texture2D.h"
#include "SmartDraw.h"

void Sample1_State::InitState() {

	std::cout << "State initialized." << std::endl;
	_tex1 = new Texture2D("test/test1.png");
	_draw = new SmartDraw;
}

void Sample1_State::UpdateState() {

}

void Sample1_State::RenderState() {

	_draw->DrawQuad(glm::vec2(20, 20), glm::vec2(200, 200), glm::vec4(1, 1, 1, 1));

}