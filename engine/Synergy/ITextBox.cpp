#include "ITextBox.h"
#include "SynUI.h"
#include "ITheme.h"
#include "Texture2D.h"
#include "GLFW/glfw3.h"

std::string toLowerCase(const std::string& str) {
	std::string lowerCaseStr;
	for (char c : str) {
		lowerCaseStr += std::tolower(c);
	}
	return lowerCaseStr;
}

ITextBox::ITextBox() {

	_ScissorTest = true;
	_Image = SynUI::Theme->_DarkFrame;

}

void ITextBox::TextChanged() {

//	_ClaretX = _Text.size();
//	_StartX = 4;

}

void ITextBox::OnKey(int key) {

	std::cout << "Key:" << key << std::endl;

	switch (key) {
	case GLFW_KEY_BACKSPACE:

		if (_ClaretX > 0)
		{

			if (_ClaretX == 1)
			{
				_Text = _Text.substr(1);
			}
			else {
				_Text = _Text.substr(0, _ClaretX - 1) + _Text.substr(_ClaretX);
			}
			_ClaretX--;
			if (_ClaretX <= _StartX)
			{
				_StartX = _ClaretX - 5;
				if (_StartX < 0) _StartX = 0;
				if (_ClaretX < 0) _ClaretX = 0;
			}
		}

		return;
		break;
	case GLFW_KEY_DELETE:

		if (_ClaretX < _Text.size()) {

			_Text = _Text.substr(0, _ClaretX) + _Text.substr(_ClaretX + 1);
			//_Tex6t = _Text + 


		}
		return;

		break;
	case GLFW_KEY_RIGHT:
	{
		int tc = _ClaretX;
		if (tc < _Text.size()) {
			_ClaretX++;
		
			int mf = _ClaretX - _StartX;

			if (mf > MaxString(_Text).size() - 1)
			{
				_StartX++;
			}
		
		}
		return;
	}
		break;
	case GLFW_KEY_LEFT:
		if (_ClaretX > 0)
		{
			_ClaretX--;
			if (_ClaretX < _StartX)
			{
				if (_StartX > 0) {
					_StartX--;
				}
			}
		}
		return;
		break;
	}

	std::string k = GetChr(key);

	//add char

	if (_ClaretX == _Text.size()) {

		_Text = _Text + k;
		_ClaretX++;
	}else if (_ClaretX == 0)
	{
		if (_Text.size() == 0)
		{
			_Text = k;
			_ClaretX++;
		}
		else {
			_Text = k + _Text;
			_ClaretX++;
		}
	}
	else {

		_Text = _Text.substr(0, _ClaretX) + k + _Text.substr(_ClaretX);
		_ClaretX++;

	}

	

	//_Text = _Text + k;


	//_ClaretX++;


	if (_ClaretX >= _Text.size()) {
		_ClaretX = _Text.size();
	}

	int ax = _ClaretX - _StartX;
	//auto cc = MaxString(_Text);

	int tw = 0;
	for (int i = _StartX; i < _Text.size(); i++) {

		tw += SynUI::StrW(_Text.substr(i,1));
		if (tw >= _Size.x)
		{
			_StartX++;
		}
	}



	
	//	if (ax >= _DisLen) {
//		_StartX++;
	//}


}


std::string ITextBox::GetChr(int key) {

	std::string r = "";

	switch (key) {
	case GLFW_KEY_MINUS:
		r = "-";
		break;
	case GLFW_KEY_EQUAL:
		r = "=";
		break;
	case GLFW_KEY_LEFT_BRACKET:
		r = "[";
		break;
	case GLFW_KEY_RIGHT_BRACKET:
		r = "]";
		break;
	case 92:
		r = "\\";
		break;
	case GLFW_KEY_APOSTROPHE:
		r = "'";
		break;
	case 162:
		r = "\\";
		break;
	case GLFW_KEY_COMMA:
		r = ",";
		break;
	case GLFW_KEY_PERIOD:
		r = ".";
		break;
	case 47:
		r = "/";
		break;
	case GLFW_KEY_SPACE:
		r = " ";
		break;
	case GLFW_KEY_A:
		r = "A";
		break;
	case GLFW_KEY_B:
		r = "B";
		break;
	case GLFW_KEY_C:
		r = "C";
		break;
	case GLFW_KEY_D:
		r = "D";
		break;
	case GLFW_KEY_E:
		r = "E";
		break;
	case GLFW_KEY_F:
		r = "F";
		break;
	case GLFW_KEY_G:
		r = "G";
		break;
	case GLFW_KEY_H:
		r = "H";
		break;
	case GLFW_KEY_I:
		r = "I";
		break;
	case GLFW_KEY_J:
		r = "J";
		break;
	case GLFW_KEY_K:
		r = "K";
		break;
	case GLFW_KEY_L:
		r = "L";
		break;
	case GLFW_KEY_M:
		r = "M";
		break;
	case GLFW_KEY_N:
		r = "N";
		break;
	case GLFW_KEY_O:
		r = "O";
		break;
	case GLFW_KEY_P:
		r = "P";
		break;
	case GLFW_KEY_Q:
		r = "Q";
		break;
	case GLFW_KEY_R:
		r = "R";
		break;
	case GLFW_KEY_S:
		r = "S";
		break;
	case GLFW_KEY_T:
		r = "T";
		break;
	case GLFW_KEY_U:
		r = "U";
		break;
	case GLFW_KEY_V:
		r = "V";
		break;
	case GLFW_KEY_W:
		r = "W";
		break;
	case GLFW_KEY_X:
		r = "X";
		break;
	case GLFW_KEY_Y:
		r = "Y";
		break;
	case GLFW_KEY_Z:
		r = "Z";
		break;
	case GLFW_KEY_0:
		r = "0";
		break;
	case GLFW_KEY_1:
		r = "1";
		break;
	case GLFW_KEY_2:
		r = "2";
		break;
	case GLFW_KEY_3:
		r = "3";
		break;
	case GLFW_KEY_4:
		r = "4";
		break;
	case GLFW_KEY_5:
		r = "5";
		break;
	case GLFW_KEY_6:
		r = "6";
		break;
	case GLFW_KEY_7:
		r = "7";
		break;
	case GLFW_KEY_8:
		r = "8";
		break;
	case GLFW_KEY_9:
		r = "9";
		break;
	case 59:
		r = ";";
		break;
	case GLFW_KEY_TAB:
		r = "	";
		break;
	}
	
	if (_ShiftOn) {
		switch (key) {
		case 59:
			r = ":";
			break;
		case 47:
			r = "?";
			break;
		case GLFW_KEY_MINUS:
			r = "+";
			break;
		case GLFW_KEY_EQUAL:
			r = "+";
			break;
		case GLFW_KEY_LEFT_BRACKET:
			r = "{";
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			r = "}";
			break;
		case 92:
			r = "|";
			break;
		case GLFW_KEY_COMMA:
			r = "<";
			break;
		case GLFW_KEY_PERIOD:
			r = ">";
			break;
		case GLFW_KEY_APOSTROPHE:
			r = "\"";
			break;
		case 162:
			r = "|";
			break;
		case GLFW_KEY_0:
			r = ")";
			break;
		case GLFW_KEY_1:
			r = "!";
			break;
		case GLFW_KEY_2:
			r = "@";
			break;
		case GLFW_KEY_3:
			r = "#";
			break;
		case GLFW_KEY_4:
			r = "$";
			break;
		case GLFW_KEY_5:
			r = "%";
			break;
		case GLFW_KEY_6:
			r = "^";
			break;
		case GLFW_KEY_7:
			r = "&";
			break;
		case GLFW_KEY_8:
			r = "*";
			break;
		case GLFW_KEY_9:
			r = "(";
			break;
		};
	}else{
			r = toLowerCase(r);
		
	}

	return r;
}



void ITextBox::Render() {

	auto pos = GetRenderPosition();
	//SynUI::Draw(SynUI::Theme->_Frame, pos+glm::vec2(-1,-1), GetSize()+glm::vec2(2,2), glm::vec4(4, 4, 4, 1));


	SynUI::Draw(_Image, pos, GetSize(), glm::vec4(1, 1, 1, 1));
	
	std::string display_Str = MaxString(_Text);
	_DisLen = display_Str.size();

	SynUI::DrawStr(display_Str, glm::vec2(pos.x+3,pos.y+5), glm::vec4(1, 1, 1, 1));

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

int ITextBox::MaxChars() {

	return 0;

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