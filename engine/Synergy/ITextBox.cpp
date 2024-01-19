#include "ITextBox.h"
#include "SynUI.h"
#include "ITheme.h"
#include "Texture2D.h"

ITextBox::ITextBox() {

	_Image = SynUI::Theme->_Frame;

}

void ITextBox::TextChanged() {

	_ClaretX = _Text.size();

}

void ITextBox::Render() {

	auto pos = GetRenderPosition();
	SynUI::Draw(_Image, pos, GetSize(), glm::vec4(1, 1, 1, 1));
	
	std::string display_Str = MaxString(_Text);

	SynUI::DrawStr(display_Str, glm::vec2(pos.x+3,pos.y+4), glm::vec4(1, 1, 1, 1));

	if (_Active) {

		int cx = pos.x + 3;

		if (_ClaretOn) {

			cx = GetClaretX();

			SynUI::Draw(_Image, glm::vec2(pos.x+cx, pos.y), glm::vec2(2, GetSize().y), glm::vec4(2, 2, 2, 1));

		}
	
	}
}

int ITextBox::GetClaretX() {

	int nx = _ClaretX - _StartX;
	auto str = MaxString(_Text);
	auto mstr = str.substr(0, nx);
	return SynUI::StrW(mstr) + 4;


}

std::string ITextBox::GetString(std::string text, int s, int e)
{
	auto str = text.substr(s);
	str = MaxString(str);
	return str;

}

std::string ITextBox::MaxString(std::string str)
{

	std::string res = "";
	for (int i = _StartX; i < str.size(); i++) {

		std::string nc = str.substr(i, 1);

		int aw = SynUI::StrW(res + nc);
		if (aw < GetSize().x)
		{
			res = res + nc;
		}
		else {
			return res;
		}

	}

	return res;

}

void ITextBox::OnActivate() {
	_Active = true;
	_ClaretOn = true;
	_NextClaret = clock();

}

void ITextBox::OnDeactivate() {
	_Active = false;
}

void ITextBox::Update(float dt) {

	int time = clock();
	if (time > _NextClaret + 500)
	{
		_NextClaret = time;
		_ClaretOn = _ClaretOn ? false : true;
	}

}