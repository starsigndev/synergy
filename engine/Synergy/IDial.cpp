#include "IDial.h"
#include "SynUI.h"
#include "ITheme.h"
#include "Texture2D.h"
IDial::IDial() {

	_ScissorTest = false;
	_Outline = false;
	_Value = 0.5f;
	_LineTex = Texture2D::WhiteTexture();
}

float IDial::GetValue() {

	return _Value;

}

void IDial::SetValue(float value) {

	if (value > 1.0) value = 1.0f;
	_Value = value;

}

void IDial::OnMouseDown(int button) {

	_Dragging = true;

}

void IDial::OnMouseUp(int button) {

	_Dragging = false;

}

void IDial::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	if (_Dragging) {
		_Value += delta.x * 0.002f;
		if (_Value > 1.0f) _Value = 1.0f;
		if (_Value < 0.0f) _Value = 0.0f;
	}
}


void IDial::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_Circle, pos, GetSize(), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	float max_ang = _Value * 360.0f;


	float cv = 0.3f;



	float lx, ly;
	bool first = true;
	for (float ang = 0; ang < max_ang+5; ang += 5)
	{

		float av = ang / 360.0f;

		av = av * 0.7f;

		cv = 0.3f + av;

		float xp = (pos.x + GetSize().x / 2 + cos(glm::radians(ang)) * ((GetSize().x / 2)*0.725f));
		float yp = (pos.y + GetSize().y / 2 + sin(glm::radians(ang)) * ((GetSize().x / 2)*0.725f));

		if (!first) {

			SynUI::DrawLine(_LineTex, glm::vec2(lx, ly), glm::vec2(xp, yp), glm::vec4(0,cv,cv, 1.0f));

		}
		else {
			first = false;
		}

		lx = xp;
		ly = yp;
	}

}