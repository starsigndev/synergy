#include "Sample1_State.h"
#include <iostream>
#include "Texture2D.h"
#include "SmartDraw.h"
#include "SynApp.h"
#include "RndNum.h"

void Sample1_State::InitState() {

	std::cout << "State initialized." << std::endl;
	_tex1 = new Texture2D("test/test1.png");
	_draw = new SmartDraw;
}

void Sample1_State::UpdateState() {

}

void Sample1_State::RenderState() {

	
	_draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());

	_draw->Begin();
	for (int i = 0;i < 10000;i++) {
		
		int x = StaticRandom::Int(0, 1024);
		int y = StaticRandom::Int(0, 768);
		_draw->DrawQuad(_tex1, glm::vec2(x, y), glm::vec2(100, 100), glm::vec4(1, 1, 1, 1));
		
		//_draw->DrawQuad(_tex1, glm::vec2(200, 50), glm::vec2(200, 100), glm::vec4(1, 1, 1, 1));
		//_draw->DrawQuad(_tex1, glm::vec2(50, 200), glm::vec2(180, 120), glm::vec4(1, 1, 1, 1));
		//_draw->DrawQuad(_tex1, glm::vec2(300, 250), glm::vec2(150, 170), glm::vec4(1, 1, 1, 1));
	}
	_draw->End();


}