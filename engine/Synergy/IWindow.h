#pragma once
#include "IControl.h"

class IButton;
class IFrame;
class IVScroller;
class IDragZone;
class IWindowTitle;
class IWindowDock;
class IWindowContent;

class IWindow : public IControl
{
public:
	
	IWindow(bool vertical_scroller=false);
	void SizeChanged();
	void TextChanged();
	IWindowContent* GetContent() {
		return _Content;
	}
	void Update(float dt);
	void Render();
	void SetDock(IWindowDock* dock);
	IWindowDock* GetDock();
	void RemoveSizers();
	IVScroller* GetScroller() {
		return _VScroller;
	}
protected:

	IWindowTitle* _Title;
	IWindowContent* _Content;
	IVScroller* _VScroller = nullptr;
	IButton* _Resizer;
	IDragZone* _Left, * _Top, * _Right, * _Bottom;
	IWindowDock* _Dock = nullptr;
	

};

