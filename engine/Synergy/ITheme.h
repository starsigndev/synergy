#pragma once
#include "glm/glm.hpp"
class FontRender;
class Texture2D;

class ITheme
{
public:

	Texture2D* _Cursor;
	Texture2D* _Button;
	Texture2D* _Frame;
	Texture2D* _DarkFrame;
	Texture2D* _TitleBar;
	FontRender* _Font;
	Texture2D* _ArrowRight;
	glm::vec4 _FontFore;
	glm::vec4 _FontBack;

};

