#include "IWindow.h"

#include "IButton.h"
#include "IFrame.h"
#include "IVScroller.h"
#include "ITheme.h"
#include "SynUI.h"

IWindow::IWindow(bool vertical_scroller) {

	_Title = new IButton;
	_Title->SetImage(SynUI::Theme->_TitleBar);
	_Content = new IFrame;
	_Content->SetPosition(glm::vec2(0, 21));
	_Title->SetText("Window");
	_Resizer = new IButton;
	_Resizer->SetSize(glm::vec2(15, 13));

	AddControl(_Resizer);
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

	_Resizer->OnDrag = [&](glm::vec2 delta)
		{
		
			glm::vec2 nsize=glm::vec2(_Size.x + delta.x, _Size.y + delta.y);
			if (nsize.x < 128) nsize.x = 128;
			if (nsize.y < 64) nsize.y = 64;
			SetSize(nsize);
			_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
		};

	_Title->OnDrag=[&](glm::vec2 delta)
	{

			SetPosition(GetPosition() + delta);
			_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));

	};
	if (vertical_scroller) {


		//_VScroller->SetPosition(glm::vec2(0,))

	}

}

void IWindow::TextChanged() {

	_Title->SetText(_Text);
	

}

void IWindow::SizeChanged() {

	_Title->SetSize(glm::vec2(GetSize().x, 20));
	_Content->SetSize(glm::vec2(_Size.x-15, _Size.y - 21));
	_VScroller->SetPosition(glm::vec2(_Size.x - 15, 21));
	_VScroller->SetSize(glm::vec2(15, _Size.y - 36));
	_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
	_Resizer->SetPosition(glm::vec2(_Size.x - 15, _Size.y - 13));
	_Resizer->SetText("*");
}

void IWindow::Update(float dt) {

	int my = 0;

	if (_VScroller != nullptr) {

		for (auto const& c : _Content->GetControls()) {

			int ay = c->GetPosition().y +c->GetSize().y;
			ay = ay - _Content->GetSize().y;
			if (ay > my)
			{
				my = ay;
			}

		}
		
		_VScroller->SetMaxValue(my);

	}

}

void IWindow::Render() {

	auto pos = GetRenderPosition();

	SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(pos.x - 1, pos.y - 1), glm::vec2(GetSize().x + 2, GetSize().y + 2), glm::vec4(4, 4, 4, 1));

}