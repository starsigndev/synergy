#include "IToggle.h"
#include "SynUI.h"
#include "ITheme.h"

IToggle::IToggle() {

}

void IToggle::OnMouseDown(int button) {

	_Enabled = _Enabled ? false : true;


}

bool IToggle::GetEnabled() {

	return _Enabled;

}

void IToggle::SetEnabled(bool enable) {

	_Enabled = enable;

}

void IToggle::SetLabel(std::string label) {

	_Label = label;

}

void IToggle::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1, 1, 1, 1));
	if (_Enabled) {
		SynUI::Draw(SynUI::Theme->_Frame, pos + glm::vec2(2, 2), GetSize() + glm::vec2(-4, -4), glm::vec4(2.5f, 2.5f, 2.5f, 1));
	}
	SynUI::DrawStr(_Label, glm::vec2(pos.x + 24, pos.y), glm::vec4(1, 1, 1, 1));

}