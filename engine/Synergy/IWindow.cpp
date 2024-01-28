#include "IWindow.h"

#include "IButton.h"
#include "IFrame.h"
#include "IVScroller.h"
#include "ITheme.h"
#include "IDragZone.h"
#include "SynUI.h"
#include "IWindowTitle.h"
#include "IWindowContent.h"


IWindow::IWindow(bool vertical_scroller) {

	_Title = new IWindowTitle;
	_Title->SetImage(SynUI::Theme->_TitleBar);
	_Title->SetWindow(this);
	_Content = new IWindowContent;
	_Content->SetPosition(glm::vec2(0, 21));
	_Title->SetText("Window");
	_Resizer = new IButton;
	_Resizer->SetSize(glm::vec2(16, 16));
//	_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
	_Left = new IDragZone;
	_Right = new IDragZone;
	_Bottom = new IDragZone;
	_Top = new IDragZone;

	
	AddControl(_Title);
	AddControl(_Content);

	if (vertical_scroller)
	{

		_VScroller = new IVScroller();
		AddControl(_VScroller);
	


		_VScroller->OnValueChanged = [&](float value)
			{

				_Content->SetScroll(glm::vec2(0, -value * _VScroller->GetMaxValue()));

			};

	}
	AddControl(_Resizer);
	_Resizer->OnDrag = [&](glm::vec2 delta)
		{
		
			glm::vec2 nsize=glm::vec2(_Size.x + delta.x, _Size.y + delta.y);
			if (nsize.x < 128) nsize.x = 128;
			if (nsize.y < 64) nsize.y = 64;
			SetSize(nsize);
	//		_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
		};

	_Title->OnDrag=[&](glm::vec2 delta)
	{

			SetPosition(GetPosition() + delta);
			//_Content->Set
			// (glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));

	};

	_Right->OnDrag = [&](glm::vec2 delta) {

		SetSize(GetSize() + glm::vec2(delta.x, 0));

	};

	_Bottom->OnDrag = [&](glm::vec2 delta) {

		SetSize(GetSize() + glm::vec2(0, delta.y));

		};

	_Left->OnDrag = [&](glm::vec2 delta) {

		SetPosition(GetPosition() + glm::vec2(delta.x, 0));
		SetSize(GetSize() + glm::vec2(-delta.x, 0));


		};

	_Top->OnDrag = [&](glm::vec2 delta) {

		SetPosition(GetPosition() + glm::vec2(0, delta.y));
		SetSize(GetSize() + glm::vec2(0, -delta.y));

		};

	if (vertical_scroller) {


		//_VScroller->SetPosition(glm::vec2(0,))

	}

	AddControl(_Right);
	AddControl(_Bottom);
	AddControl(_Left);
	AddControl(_Top);

	_Right->AddTag("Cursor","LeftRight");
	_Left->AddTag("Cursor","LeftRight");
	_Top->AddTag("Cursor","UpDown");
	_Bottom->AddTag("Cursor","UpDown");
	_Outline = false;
	_Resizer->AddTag("Cursor","Resizer");


}

void IWindow::TextChanged() {

	_Title->SetText(_Text);
	

}

void IWindow::SizeChanged() {


	_Title->SetSize(glm::vec2(GetSize().x, 20));
	
	if (_VScroller) {
		_Content->SetSize(glm::vec2(_Size.x, _Size.y - 21));
		_VScroller->SetPosition(glm::vec2(_Size.x - 14, 21));
		_VScroller->SetSize(glm::vec2(13, _Size.y - 21-18));
	}
	else {
		_Content->SetSize(glm::vec2(_Size.x, _Size.y - 21));
	}
	//_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
	_Resizer->SetPosition(glm::vec2(_Size.x - 16, _Size.y - 16));
//	_Resizer->SetImage(SynUI::Theme->_WinRight);
	_Resizer->SetIcon(SynUI::Theme->_Resizer);
	_Right->SetPosition(glm::vec2(_Size.x - 2, 0));
	_Right->SetSize(glm::vec2(4, _Size.y - 4));
	_Bottom->SetPosition(glm::vec2(0, _Size.y - 2));
	_Bottom->SetSize(glm::vec2(_Size.x, 4));
	_Left->SetPosition(glm::vec2(-2, 0));
	_Left->SetSize(glm::vec2(4, _Size.y - 2));
	_Top->SetPosition(glm::vec2(0, -2));
	_Top->SetSize(glm::vec2(_Size.x, 4));
}


void IWindow::Update(float dt) {

	int my = 0;

	if (_VScroller != nullptr) {

		for (auto const& c : _Content->GetControls()) {

			int ay = c->GetPosition().y +c->GetSize().y;
		//	ay = ay - c->GetSize().y;
			if (ay > my)
			{
				my = ay;
			}

		}
		
		my = my - GetContent()->GetSize().y+100;
		_VScroller->SetMaxValue(my);

	}

}

void IWindow::Render() {

	auto pos = GetRenderPosition();

//	SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x - 1, pos.y - 1), glm::vec2(GetSize().x + 2, GetSize().y + 2), glm::vec4(4, 4, 4, 1));

}

void IWindow::SetDock(IWindowDock* dock) {

	_Dock = dock;
	if (_Dock) {
		_Content->SetDocked(true);
	}
	else {
		_Content->SetDocked(false);
	}

}

IWindowDock* IWindow::GetDock() {

	return _Dock;

}

void IWindow::RemoveSizers() {

	RemoveControl(_Left);
	RemoveControl(_Right);
	RemoveControl(_Top);
	RemoveControl(_Bottom);
	RemoveControl(_Resizer);

}