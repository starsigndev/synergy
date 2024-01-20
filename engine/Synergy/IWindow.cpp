#include "IWindow.h"

#include "IButton.h"
#include "IFrame.h"
#include "IVScroller.h"

IWindow::IWindow(bool vertical_scroller) {

	_Title = new IButton;
	_Content = new IFrame;
	_Content->SetPosition(glm::vec2(0, 25));
	_Title->SetText("Window");

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

	_Title->SetSize(glm::vec2(GetSize().x, 25));
	_Content->SetSize(glm::vec2(_Size.x-15, _Size.y - 25));
	_VScroller->SetPosition(glm::vec2(_Size.x - 15, 25));
	_VScroller->SetSize(glm::vec2(15, _Size.y - 25));
	_Content->SetScissor(glm::vec4(_Content->GetRenderPosition().x, _Content->GetRenderPosition().y, _Content->GetSize().x, _Content->GetSize().y));
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