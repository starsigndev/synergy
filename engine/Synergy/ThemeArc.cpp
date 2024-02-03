#include "ThemeArc.h"
#include "Texture2D.h"
#include "FontRender.h"

ThemeArc::ThemeArc() {

	_Button = new Texture2D("ui/theme/arc/button.png",true);
	_Frame = new Texture2D("ui/theme/arc/frame.png", true);
	_Cursor = new Texture2D("ui/theme/arc/cursor_normal.png",true);
	_LeftRightCursor = new Texture2D("ui/theme/arc/leftrightarrow.png", true);
	_UpDownCursor = new Texture2D("ui/theme/arc/updownarrow.png", true);
	_ResizeCursor = new Texture2D("ui/theme/arc/resizearrow.png", true);
	_TitleBar = new Texture2D("ui/theme/arc/titlebar.png", true);
	_DarkFrame = new Texture2D("ui/theme/arc/darkframe.png", true);
	_Font = new FontRender("fonts/system6.ttf");
	_ArrowRight = new Texture2D("ui/theme/arc/arrowright.png", true);
	_Resizer = new Texture2D("ui/theme/arc/resizer.png", true);
	_FontFore = glm::vec4(1,1,1, 1.0f);
	_FontBack = glm::vec4(0, 0, 0, 1.0f);
	_Translate = new Texture2D("ui/theme/arc/translate.png",true);
	_Rotate = new Texture2D("ui/theme/arc/rotate.png",true);
	_Scale = new Texture2D("ui/theme/arc/scale.png",true);
	_NewScene = new Texture2D("ui/theme/arc/newscene.png", true);
	_Circle = new Texture2D("ui/theme/arc/circle.png", true);
	_WindowFrame = new Texture2D("ui/theme/arc/windowframe.png", true);
	_AppFrame = new Texture2D("ui/theme/arc/appframe.png", true);
	_WinLeft = new Texture2D("ui/theme/arc/LeftFrameR.png", true);
	_WinRight = new Texture2D("ui/theme/arc/RightFrameR.png", true);
	_WinMid = new Texture2D("ui/theme/arc/midframeR.png", true);
	_Minimize = new Texture2D("ui/theme/arc/minimize.png", true);
	_Maximize = new Texture2D("ui/theme/arc/maximize.png", true);
	_CloseApp = new Texture2D("ui/theme/arc/closeapp.png", true);
	_RunGame = new Texture2D("ui/theme/arc/runicon.png", true);
	_StopGame = new Texture2D("ui/theme/arc/stopicon.png", true);

}