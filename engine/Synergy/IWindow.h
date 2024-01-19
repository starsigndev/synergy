#pragma once
#include "IControl.h"

class IButton;
class IFrame;

class IWindow : public IControl
{
public:

	IWindow();
	void SizeChanged();
	void TextChanged();
	IFrame* GetContent() {
		return _Content;
	}

private:

	IButton* _Title;
	IFrame* _Content;
	

};

