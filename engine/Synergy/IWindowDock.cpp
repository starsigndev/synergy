#include "IWindowDock.h"
#include "SynUI.h"
#include "ITheme.h"
#include "IWindow.h"
#include <iostream>
#include "AppInput.h"

IWindowDock::IWindowDock() {

	_ALeft = nullptr;
	_ARight = nullptr;
	_ATop = nullptr;
	_ABottom = nullptr;
	_ACentral = nullptr;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			_Used[x][y] = false;
		}
	}

	_Outline = false;

}

void IWindowDock::SizeChanged() {


	CreateInitialAreas();
	


}


void IWindowDock::CreateInitialAreas() {

	_Areas.clear();


	//Top
	DockArea* top = new DockArea;
	top->Position = glm::vec2(0, 0);
	top->Size = glm::vec2(_Size.x, _Size.y / 4);
	top->Name = AreaTop;
	top->AreaPosition = glm::vec2(_Size.x / 2 - 128,top->Size.y/2-64);
	top->AreaSize = glm::vec2(256, 128);

	_ATop = top;

	DockArea* bottom = new DockArea;
	bottom->Position = glm::vec2(0, _Size.y-_Size.y/4);
	bottom->Size = glm::vec2(_Size.x, _Size.y / 4);
	bottom->Name = AreaBottom;
	bottom->AreaPosition = glm::vec2(_Size.x / 2 - 128, bottom->Position.y+bottom->Size.y*0.5-64);
	bottom->AreaSize = glm::vec2(256, 128);

	DockArea* left = new DockArea;
	left->Position = glm::vec2(0,0);
	left->Size = glm::vec2(_Size.x/4, _Size.y);
	left->Name = AreaLeft;
	left->AreaPosition = glm::vec2(left->Size.x/2-64,left->Size.y/2-64);
	left->AreaSize = glm::vec2(128,128);

	DockArea* right = new DockArea;
	right->Position = glm::vec2(_Size.x-_Size.x/4, 0);
	right->Size = glm::vec2(_Size.x / 4, _Size.y);
	right->Name = AreaRight;
	right->AreaPosition = glm::vec2(right->Position.x+right->Size.x/2-64,right->Position.y+right->Size.y/2-64);
	right->AreaSize = glm::vec2(128, 128);

	DockArea* cent = new DockArea;
	cent->Position = glm::vec2(_Size.x/4,_Size.y/4);
	cent->Size = glm::vec2(_Size.x/2, _Size.y/2);
	cent->Name = AreaCentral;
	cent->AreaPosition = glm::vec2(cent->Position.x+cent->Size.x/2 - 64, cent->Position.y+cent->Size.y/2 - 64);
	cent->AreaSize = glm::vec2(128, 128);


	_ATop = top;
	_ABottom = bottom;
	_ALeft = left;
	_ARight = right;
	_ACentral = cent;

	_Areas.push_back(top);
	_Areas.push_back(bottom);
	_Areas.push_back(left);
	_Areas.push_back(right);
	_Areas.push_back(cent);
}


void IWindowDock::WindowOver(IWindow* win) {

	std::cout << "Window over:" << win->GetText() << std::endl;
	
	auto area = GetAreaDock(AppInput::_MousePosition-GetRenderPosition());
	_OverArea = area;

}

void IWindowDock::SetDockArea(DockArea* area, IWindow* win,bool change) {


		auto dpos = area->Position;
		auto dsize = area->Size;

		bool i1, i2, i3;

		area->Docked = win;


		i1 = i2 = i3 = true;
		switch (area->Name) {

		case AreaTop:

			if (_Used[0][0])
			{
				dpos.x += _Size.x / 4;
				dsize.x -= _Size.x / 4;
				i1 = false;
			}
			if (_Used[1][0]) {
				dpos.x += _Size.x / 4;
				dsize.x -= _Size.x / 4;
				i2 = false;
			}
			if (_Used[2][0])
			{
				dsize.x -= _Size.x / 4;
				i3 = false;

			}

			if (i1) {
				_Used[0][0] = i1;
			}
			if (i2) {
				_Used[1][0] = i2;
			}

			if (i3) {
				_Used[2][0] = i3;
			}
			area->_Taken[0][0] = i1;
			area->_Taken[1][0] = i2;
			area->_Taken[2][0] = i3;

			break;
		case AreaBottom:

			if (_Used[0][2])
			{
				dpos.x += _Size.x / 4;
				dsize.x -= _Size.x / 4;
				i1 = false;
			}
			if (_Used[1][2]) {
				dpos.x += _Size.x / 4;
				dsize.x -= _Size.x / 4;
				i2 = false;
			}
			if (_Used[2][2])
			{
				dsize.x -= _Size.x / 4;
				i3 = false;

			}

			if (i1) {
				_Used[0][2] = i1;
			}
			if (i2) {
				_Used[1][2] = i2;
			}

			if (i3) {
				_Used[2][2] = i3;
			}

			break;
		case AreaRight:
			if (_Used[2][0]) {

				dpos.y += _Size.y / 4;
				dsize.y -= _Size.y / 4;
				i1 = false;

			}
			if (_Used[2][1]) {

				dpos.y += _Size.y / 4;
				i2 = false;

			}

			if (_Used[2][2]) {

				dsize.y -= _Size.y / 4;
				i3 = false;
			}

			if (i1) {
				_Used[2][0] = i1;
			}
			if (i2) {
				_Used[2][1] = i2;
			}
			if (i3) {
				_Used[2][2] = i3;
			}

			break;
		case AreaLeft:


		

			if (_Used[0][0]) {

				dpos.y += _Size.y / 4;
				dsize.y -= _Size.y / 4;
				i1 = false;

			}
			if (_Used[0][1]) {

				dpos.y += _Size.y / 4;
				i2 = false;

			}

			if (_Used[0][2]) {

				dsize.y -= _Size.y / 4;
				i3 = false;
			}

			if (i1) {
				_Used[0][0] = i1;
			}
			if (i2) {
				_Used[0][1] = i2;
			}
			if (i3) {
				_Used[0][2] = i3;
			}
			area->_Taken[0][0] = i1;
			area->_Taken[0][1] = i2;
			area->_Taken[0][2] = i3;


			break;
		case AreaCentral:

			int xval[3];
			int yval[3];
			int xs[3];
			int ys[3];

			xval[0] = 0;
			xval[1] = _Size.x / 4;
			xval[2] = xval[1] + _Size.x / 2;
			yval[0] = 0;
			yval[1] = _Size.y / 4;
			yval[2] = yval[1] + _Size.y / 2;
			xs[0] = _Size.x;
			ys[0] = _Size.y;
			xs[1] = _Size.x - _Size.x / 4;
			ys[1] = _Size.y - _Size.y / 4;
			xs[2] = _Size.x / 4;
			ys[2] = _Size.y / 4;




			int sx, sy;
			int dx, dy;
			dx = 1;
			dy = 1;
			sx = sy = 0;
			dpos.y = 0;
			
			bool first = true;

			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {

					if (_Used[x][y])
					{
						
					}
					else {

						if (first) {
							sx = x;
							sy = y;
							first = false;
						}
						else {
							dx = x;
							dy = y;
							//break;
						}

					}

				}
			}

			dpos.x = xval[sx];
			dpos.y = yval[sy];
			dsize.x = xs[2-(dx-sx)];
			dsize.y = ys[2-(dy-sy)];
			if (dx == sx) {
				dsize.x = _Size.x / 2;
			}
			if (dy == sy) {
				dsize.y = _Size.y / 2;
			}

			int b = 5;

			//dsize.x = 256;
			//dsize.y = 256;

			//int b = 5;


			break;
		}

		win->SetPosition(dpos);
		win->SetSize(dsize);
		if (change) {
			_Areas.erase(std::remove(_Areas.begin(), _Areas.end(), area), _Areas.end());
			_Areas.push_back(area);
			//->Docked = win;
		}



}

void IWindowDock::WindowDropped(IWindow* win) {

	if (_OverArea) {
		SetDockArea(_OverArea, win,true);
		win->SetDock(this);
		win->GetRootControl()->RemoveControl(win);
		win->GetRootControl()->InsertControl(win,2);
	//	win->GetRootControl()->GetDock()->InsertControl(win);

		//auto controls = win->GetControls();

		_OverArea = nullptr;
	}

	return;
	//if (_OverArea) {


}

DockArea* IWindowDock::GetArea(glm::vec2 pos) {

	for (auto const& area : _Areas) {

		if (pos.x >= area->Position.x && pos.x <= area->Position.x + area->Size.x)
		{
			if (pos.y > area->Position.y && pos.y <= area->Position.y + area->Size.y)
			{
				return area;
			}
		}

	}

	return nullptr;

}


DockArea* IWindowDock::GetAreaDock(glm::vec2 pos) {

	for (auto const& area : _Areas) {

		if (pos.x >= area->AreaPosition.x && pos.x <= area->AreaPosition.x + area->AreaSize.x)
		{
			if (pos.y > area->AreaPosition.y && pos.y <= area->AreaPosition.y + area->AreaSize.y)
			{
				return area;
			}
		}

	}

	return nullptr;

}




void IWindowDock::Render() {


	auto pos = GetRenderPosition();

	for (auto const& area : _Areas) {

		if (area == _OverArea) {
			SynUI::Draw(SynUI::Theme->_Frame, pos + area->Position, area->Size, glm::vec4(0, 3, 3, 0.5f));
		}
		else {
			SynUI::Draw(SynUI::Theme->_Frame, pos + area->Position, area->Size, glm::vec4(0, 1, 1, 0.5f));
		}
		SynUI::Draw(SynUI::Theme->_Frame, pos + area->AreaPosition, area->AreaSize, glm::vec4(2, 2, 2, 0.5f));

	}
	
}

void IWindowDock::ClearDocked(IWindow* win) {

	bool rem = false;

	if (win->GetDock()) {

		int b = 5;

	}

	for (auto const& area : _Areas) {

		if (area->Docked == win) {
			area->Docked = nullptr;
			win->SetDock(nullptr);
			rem = true;
		}
		//	WindowDropped(win);

		


	}

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {

			_Used[x][y] = false;

		}
	}

	for (auto const& area : _Areas) {

		if (area->Docked!=nullptr) {
			SetDockArea(area, (IWindow*)area->Docked,false);
			//	area->Docked = nullptr;
		}

		//	WindowDropped(win);




	}
}