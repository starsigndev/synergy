#pragma once
#include "glm/glm.hpp"
class FontRender;
class Texture2D;

class ITheme
{
public:

	Texture2D* _Cursor;
	Texture2D* _LeftRightCursor;
	Texture2D* _UpDownCursor;
	Texture2D* _ResizeCursor;
	Texture2D* _Button;
	Texture2D* _Frame;
	Texture2D* _DarkFrame;
	Texture2D* _TitleBar;
	FontRender* _Font;
	Texture2D* _ArrowRight;
	Texture2D* _Resizer;
	glm::vec4 _FontFore;
	glm::vec4 _FontBack;
	//editor
	Texture2D* _Translate;
	Texture2D* _Rotate;
	Texture2D* _Scale;

};

