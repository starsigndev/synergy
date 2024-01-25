#include "IWindowContent.h"
#include "ITheme.h"
#include "SynUI.h"

IWindowContent::IWindowContent() {

	SetScissor(true);
	_Image = SynUI::Theme->_WindowFrame;
	_Outline = true;
	_OutlineImage = _Image;

}