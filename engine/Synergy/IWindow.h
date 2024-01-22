#pragma once
#include "IControl.h"

class IButton;
class IFrame;
class IVScroller;
class IDragZone;

class IWindow : public IControl
{
public:

	IWindow(bool vertical_scroller);
	void SizeChanged();
	void TextChanged();
	IFrame* GetContent() {
		return _Content;
	}
	void Update(float dt);
	void Render();

private:

	IButton* _Title;
	IFrame* _Content;
	IVScroller* _VScroller;
	IButton* _Resizer;
	IDragZone* _Left, * _Top, * _Right, * _Bottom;
	

};

