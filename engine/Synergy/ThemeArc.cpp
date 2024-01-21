#include "ThemeArc.h"
#include "Texture2D.h"
#include "FontRender.h"

ThemeArc::ThemeArc() {

	_Button = new Texture2D("ui/theme/arc/button.png",true);
	_Frame = new Texture2D("ui/theme/arc/frame.png", true);
	_Cursor = new Texture2D("ui/theme/arc/cursor_normal.png",true);
	_TitleBar = new Texture2D("ui/theme/arc/titlebar.png", true);
	_DarkFrame = new Texture2D("ui/theme/arc/darkframe.png", true);
	_Font = new FontRender("fonts/systemfont.ttf");
	_ArrowRight = new Texture2D("ui/theme/arc/arrowright.png", true);
	_FontFore = glm::vec4(1,1,1, 1.0f);
	_FontBack = glm::vec4(0, 0, 0, 1.0f);

}