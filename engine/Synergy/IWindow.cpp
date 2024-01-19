#include "IWindow.h"

#include "IButton.h"
#include "IFrame.h"

IWindow::IWindow() {

	_Title = new IButton;
	_Content = new IFrame;
	_Content->SetPosition(glm::vec2(0, 25));
	_Title->SetText("Window");
	AddControl(_Title);
	AddControl(_Content);
	_Title->OnDrag=[&](glm::vec2 delta)
	{

			SetPosition(GetPosition() + delta);

	};

}

void IWindow::TextChanged() {

	_Title->SetText(_Text);
	

}

void IWindow::SizeChanged() {

	_Title->SetSize(glm::vec2(GetSize().x, 25));
	_Content->SetSize(glm::vec2(_Size.x, _Size.y - 25));

}