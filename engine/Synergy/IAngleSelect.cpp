#include "IAngleSelect.h"
#include "SynUI.h"
#include "ITheme.h"
#include "Texture2D.h"

IAngleSelect::IAngleSelect() {

	_Outline = false;
	_LineTex = Texture2D::WhiteTexture();

}

void IAngleSelect::OnMouseMove(glm::vec2 pos,glm::vec2 delta) {

	float xo = pos.x - (GetSize().x / 2);// -pos.x;
	float yo = pos.y - (GetSize().y / 2);

	_EditAngle = glm::degrees(atan2(yo, xo));
	if (_Dragging) {
		_Angle = _EditAngle;
	}


}

void IAngleSelect::OnMouseDown(int button) {

	//_Angle = _EditAngle;
	_Dragging = true;

}

void IAngleSelect::OnMouseUp(int button) {

	_Dragging = false;

}

void IAngleSelect::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_Circle, pos, GetSize(),glm::vec4(0.5f,0.5f,0.5f,1.0f));

	float xp = cos(glm::radians(_Angle)) * ((GetSize().x / 2)*0.78f);
	float yp = sin(glm::radians(_Angle)) * ((GetSize().x / 2)*0.78f);

	glm::vec2 p1 = glm::vec2(pos.x + _Size.x / 2, pos.y + _Size.y / 2);
	glm::vec2 p2 = p1 + glm::vec2(xp, yp);


	SynUI::DrawLine(_LineTex,p1,p2,glm::vec4(1,1,1,1));

}