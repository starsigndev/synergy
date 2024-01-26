#include "SynUI.h"
#include "SynApp.h"
#include "SmartDraw.h"
#include "AppInput.h"
#include "Texture2D.h"
#include "ITheme.h"
#include "FontRender.h"
#include "IMenuBar.h"
#include "IWindow.h"
#include "IWindowDock.h"
#include "IWindowTitle.h"
#include "IWindowContent.h"
#include "IToolbar.h"
#include "IMenuBar.h"
#include "IVMenu.h"
#include "ThemeArc.h"
ITheme* SynUI::Theme = nullptr;
SmartDraw* SynUI::_Draw = nullptr;

SynUI* SynUI::This = nullptr;

SynUI::SynUI() {

	This = this;
	_WhiteTex = Texture2D::WhiteTexture();
	SynUI::Theme = new ThemeArc;
	_RootControl = new IControl();
	_RootControl->SetPosition(glm::vec2(0, 74));
	_RootControl->SetSize(glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight() - 76));
	_WindowDock = new IWindowDock;

	_RootControl->AddControl(_WindowDock);
	_WindowDock->SetPosition(glm::vec2(1, 1));
	_WindowDock->SetSize(_RootControl->GetSize()-glm::vec2(2,2));
	_WindowDock->SetOutline(true);

	_MenuBar = new IMenuBar;
	_MenuBar->SetPosition(glm::vec2(1, 1));
	_MenuBar->SetSize(glm::vec2(SynApp::This->GetWidth()-2, 24));
	

	_Toolbar = new IToolbar;
	_Toolbar->SetPosition(glm::vec2(0, 27));
	_Toolbar->SetSize(glm::vec2(SynApp::This->GetWidth(), 45));
	
	_Draw = new SmartDraw;
	_Draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_Cursor = new Texture2D("ui/theme/arc/cursor_normal.png");
	
}

void SynUI::Resize(int w, int h) {

	_RootControl->SetSize(glm::vec2(w, h));
	_MenuBar->SetSize(glm::vec2(w, 25));
	_Toolbar->SetSize(glm::vec2(w, _Toolbar->GetSize().y));
	_WindowDock->SetSize(glm::vec2(w, h - 25));
}

void SynUI::AddControl(IControl* control) {

	_RootControl->AddControl(control);

}

IControl* SynUI::GetRootControl() {

	return _RootControl;

}

void SynUI::UpdateUI(float dt) {


	_MousePosition = AppInput::_MousePosition;
	_MouseDelta = AppInput::_MouseDelta;
	for (int i = 0; i < 16; i++) {
		_MouseButton[i] = AppInput::_ButtonState[i];
	}

	auto list = GetListForward();

	for (auto const& control : list) {

		control->Update(dt);

	};


	UpdateMouse();
	UpdateKB();

	if (_Active) {

	}

}

bool used[512];

void SynUI::UpdateKB() {

	int pkey = _CurrentKey;


	for (int i = 0; i < 512; i++) {

		if (i == GLFW_KEY_LEFT_SHIFT) {
			continue;
		}
		if (i == GLFW_KEY_RIGHT_SHIFT) {
			continue;
		}
		if (AppInput::_KeyState[i] && used[i] == false)
		{
			if (i != _CurrentKey) {
				_FirstKey = true;
			}
			_CurrentKey = i;
			used[i] = true;
		}
		else if (AppInput::_KeyState[i]==false && used[i]) {
			used[i] = false;
		}

	}

	if (AppInput::_KeyState[GLFW_KEY_LEFT_SHIFT] || AppInput::_KeyState[GLFW_KEY_RIGHT_SHIFT])
	{
		if (_Active != nullptr) {
			_Active->SetShift(true);
		}
	}
	else {
		if (_Active != nullptr) {
			_Active->SetShift(false);
		}
	}

	if (_CurrentKey != -1 && AppInput::_KeyState[_CurrentKey] == false)
	{
		_CurrentKey = -1;
		_FirstKey = true;
		
	}

	if (_Active != nullptr) {

		if (_CurrentKey != -1)
		{
			if (_FirstKey) {
				_Active->OnKey(_CurrentKey);
				_FirstKey = false;
				_NextKey = clock() + 500;
			}
			else {
				int time = clock();
				if (time > _NextKey)
				{
					_Active->OnKey(_CurrentKey);
					_NextKey = time + 100;
				}
			}
		}

	}

}


void SynUI::UpdateMouse() {
	auto over = MouseOver(_MousePosition);

	if (_MouseButton[0]) {

		if (_Over != nullptr) {
			if (_Pressed == nullptr) {
				_Pressed = _Over;
				if (_Active) {
					if (_Active != _Over) {
						if (_Over->CanActivate()) {
							_Active->OnDeactivate();
						}
					}
				}
				if (_Active != _Over) {
					
					if (_Over->CanActivate()) {
						_Active = _Over;

						_Active->OnActivate();
						IVMenu* title = dynamic_cast<IVMenu*>(_Active);
						IMenuBar* bar = dynamic_cast<IMenuBar*>(_Active);
						if (title || bar) {

						}
						else {
							_MenuBar->ClearMenus();
						}
						//

					}
				}
				_Over->OnMouseDown(0);
			}
		}
		else {
			if (_Pressed == nullptr) {
				if (_Active)
				{
					_Active->OnDeactivate();
					_Active = nullptr;
				}
			}
		}
	}
	else {

		if (_WindowOver) {

			_WindowBelow->WindowDropped((IWindow*)_WindowOver);
			_WindowOver = nullptr;
			_WindowBelow = nullptr;

		}

		if (_Pressed != nullptr) {

			_Pressed->OnMouseUp(0);
			if (MouseOver(_MousePosition) != _Pressed)
			{
				_Pressed->OnMouseLeave();
			}
			_Pressed = nullptr;


		}

	}


	if (_Pressed == nullptr) {
		if (over != nullptr) {

			if (_Over != nullptr && _Over != over) {

				_Over->OnMouseLeave();

			}

			if (over != _Over) {
				over->OnMouseEnter();
			}
			_Over = over;


			//exit(1);


		}
		else {

			if (_Over != nullptr) {

				_Over->OnMouseLeave();

			}

			_Over = nullptr;

		}
	}

	if (_Pressed != nullptr) {

		_Pressed->OnMouseDrag(_MousePosition-_Pressed->GetRenderPosition(), _MouseDelta);

	}

	if (_Over) {

		_Over->OnMouseMove(_MousePosition - _Over->GetRenderPosition(), _MouseDelta);

	}

	if (_Pressed) {

		if (_Pressed->GetRootControl()) {



			auto root = _Pressed->GetRootControl();
			IWindow* win = dynamic_cast<IWindow*>(root);
			IWindowTitle* title = dynamic_cast<IWindowTitle*>(_Pressed);

			if (title) {

				_Ignore.clear();
				AddToIgnore(win);

				_WindowDock->ClearDocked(win);
				auto below = MouseOver(_MousePosition);

				if (below != nullptr) {
					_Ignore.clear();

					below->WindowOver(win);
					_WindowBelow = below;
					_WindowOver = win;
				}
				else {
					_WindowBelow = nullptr;
					_WindowOver = nullptr;
				}

			}





			if (win) {



				//


				if (!win->GetDock()) {
					auto win_root = win->GetRootControl();
					win_root->RemoveControl(win);
					win_root->AddControl(win);

				}

				//				if (below == _WindowDock) {

								//	_WindowDock->Wi

								//}


			}
		}

	}


}

void SynUI::AddToIgnore(IControl* control) {

	_Ignore.push_back(control);
	for (auto const& sub : control->GetControls()) {
		AddToIgnore(sub);
	}
	//_Ignore.clear();



}

bool SynUI::Ignored(IControl* con)
{
	for (auto const& ig : _Ignore) {
		if (ig == con) return true;
	}
	return false;
}

IControl* SynUI::ControlBeneath(IControl* control) {

	//auto control = MouseOver(pos);

	auto list = GetListBackward();

	IControl* prev = nullptr;
	bool next = false;

	for (auto const& sub : list) {

		if (next) {
			prev = sub;
			break;
		}
		if (control == sub) {

			next = true;
			int b = 5;

		}
		prev = sub;

	}

	return prev;


}

std::vector<IControl*> SynUI::GetListForward() {

	std::vector<IControl*> rootList;
	rootList = AddControlToList(rootList, _RootControl);
	rootList = AddControlToList(rootList, _Toolbar);
	rootList = AddControlToList(rootList, _MenuBar);

	//rootList.push_back(_MenuBar);

	return rootList;

}

std::vector<IControl*> SynUI::AddControlToList(std::vector<IControl*> list, IControl* control) {

	if (Ignored(control) == false) {
		list.push_back(control);
		auto controls = control->GetControls();

		for (const auto& con : controls) {

			list = AddControlToList(list, con);

		}
	}
	return list;

}

Texture2D* old_bg = nullptr;

void SynUI::RenderUI() {


	if (!SynApp::This->IsVisible())
	{
		return;
	}
	//auto list = GetListForward();

	auto bg = SynApp::This->GetBackground(SynApp::This->GetWindowX(),SynApp::This->GetWindowY()-_MenuBar->GetSize().y, SynApp::This->GetWidth(),_MenuBar->GetSize().y);

	if (SynApp::This->GetWidth() > 0) {
		if (old_bg) {
			old_bg->Delete();
		}

		auto tex = new Texture2D((char*)bg, SynApp::This->GetWidth(), _MenuBar->GetSize().y, 4);
		
		old_bg = tex;
		_MenuBar->SetImage(tex);
		free(bg);
	}

	glm::vec4 uv;

	uv.x = ((float)SynApp::This->GetWindowX()) / ((float)SynApp::This->ScreenW());
		uv.y = ((float)SynApp::This->GetWindowY()) / ((float)SynApp::This->ScreenH());

	uv.z = ((float)(SynApp::This->GetWindowX() + SynApp::This->GetWidth())) / ((float)SynApp::This->ScreenW());
	uv.w = ((float)(SynApp::This->GetWindowY() + _MenuBar->GetSize().y)) / ((float)SynApp::This->ScreenH());

	uv = glm::vec4(0, 1, 1, 0);

	
	_MenuBar->SetUV(uv);
	

	
	//_Draw->DrawQuad(bg, glm::vec2(0), glm::vec2(SynApp::This->GetWidth(), SynApp::This->GetHeight()), uv, glm::vec4(1, 1, 1, 1));


	 //->DrawQuad(bg, glm::vec2(0, 0), glm::vec2(512, 512), glm::vec4(1, 1, 1, 1));

	_Draw->Begin();

	//RenderList(list);
//	_Draw->SetScissor(glm::vec4( - 1, -1, -1, -1));
	RenderControl(_RootControl);

	RenderControl(_Toolbar);





	_Draw->End();

	SynApp::This->ClearZ();

	_Draw->Begin();
	RenderControl(_MenuBar);

	_Draw->End();

		SynApp::This->ClearZ();

	_Draw->Begin();
	DrawCursor();
	_Draw->End();

}

void SynUI::RenderControl(IControl* control) {

	if (control->GetOutline()) {
		if (control != _RootControl) {
			
			DrawLine(_WhiteTex, control->GetRenderPosition()+glm::vec2(-1,-1), control->GetRenderPosition() + glm::vec2(control->GetSize().x+2, -1), glm::vec4(0.5f,0.5f,0.5f, 0.8f),0.5f);
			DrawLine(_WhiteTex, control->GetRenderPosition() + glm::vec2(-1, -1) , control->GetRenderPosition() + glm::vec2(-1,control->GetSize().y+2), glm::vec4(0.5f,0.5f,0.5f,0.8f),0.5f);
			DrawLine(_WhiteTex, control->GetRenderPosition() + glm::vec2(control->GetSize().x+1, 0), control->GetRenderPosition() + glm::vec2(control->GetSize().x + 1, control->GetSize().y+1), glm::vec4(0.5f, 0.5f, 0.5f, 0.8f), 0.5f);
			DrawLine(_WhiteTex, control->GetRenderPosition() + glm::vec2(-1, control->GetSize().y+1), control->GetRenderPosition() + glm::vec2(control->GetSize().x + 2, control->GetSize().y + 1), glm::vec4(0.5f, 0.5f, 0.5f, 0.8f), 0.5f);
			if (control->GetOutlineImage()) {
			//	Draw(control->GetOutlineImage(), control->GetRenderPosition() + glm::vec2(-1, -1), control->GetSize() + glm::vec2(2, 2), glm::vec4(5, 5, 5, 1));
			}
			else {
			//	Draw(Theme->_Frame, control->GetRenderPosition() + glm::vec2(-1, -1), control->GetSize() + glm::vec2(2, 2), glm::vec4(5, 5, 5, 1));
			}
		}
	}
	
	IWindowContent* title = dynamic_cast<IWindowContent*>(control);
	
	if (title) {


		//_Draw->PushScissor(control->GetScissor());

	}

	if (control->GetScissor()) {
//		if (control->GetWholeScissor()) {
		//	_Draw->PushScissor(control->WholeBounds());
	//	}

	//	else {
			_Draw->PushScissor(control->GetBounds());
		//}
	}
	control->Render();

	if (!control->ScissorChildren()) {
		_Draw->PopScissor();
	}

	for (auto const& sub : control->GetControls()) {

		RenderControl(sub);

	}

	if (control->GetScissor() && control->ScissorChildren())
	{
		_Draw->PopScissor();

	}


}

std::vector<IControl*> SynUI::GetListBackward() {

	auto list = GetListForward();
	std::vector<IControl*> back_list;
	for (auto it = list.rbegin(); it != list.rend(); ++it) {
		//std::cout << *it << std::endl;
		back_list.push_back(*it);
	}
	return back_list;
}

void SynUI::RenderList(std::vector<IControl*> controls) {


}

void SynUI::DrawCursor() {

	//_Draw->Begin();
	bool left_right = false;
	bool up_down = false;
	bool resizer = false;

	IControl* check;

	
		check = _Over;


	if (check != nullptr) {

		if (check->HasTag("Cursor"))
		{
			auto val = check->GetTagValue("Cursor");

			if (val == "Resizer")
			{
				resizer = true;
			}
			if (val == "LeftRight")
			{

				left_right = true;

			}
			if(val == "UpDown")
			{

				up_down = true;

			}

		}

	
	}

	if (resizer) {

		_Draw->DrawQuad(Theme->_ResizeCursor, _MousePosition + glm::vec2(-16, -16), glm::vec2(32, 32), glm::vec4(1, 1, 1, 0.8f));

	}else
	if (up_down) {
		_Draw->DrawQuad(Theme->_UpDownCursor, _MousePosition + glm::vec2(0, -16), glm::vec2(16, 32), glm::vec4(1, 1, 1, 0.8f));
	}else
	if (left_right) {
		_Draw->DrawQuad(Theme->_LeftRightCursor, _MousePosition + glm::vec2(-16, 0), glm::vec2(32, 16), glm::vec4(1, 1, 1, 0.8f));
	}
	else {
		_Draw->DrawQuad(Theme->_Cursor, _MousePosition, glm::vec2(32, 32), glm::vec4(1, 1, 1, 0.8f));
	}
	//_Draw->End();


}

void SynUI::Draw(Texture2D* img, glm::vec2 pos, glm::vec2 size, glm::vec4 u,glm::vec4 v, glm::vec4 color, float blurx, float blury)
{

	_Draw->DrawQuad(img, pos, size,color,u,v, blurx, blury);

}

void SynUI::Draw(Texture2D* img, glm::vec2 pos, glm::vec2 size,glm::vec4 uv, glm::vec4 color,float blurx,float blury)
{

	_Draw->DrawQuad(img, pos, size,uv, color,blurx,blury);

}

void SynUI::Draw(Texture2D* img, glm::vec2 pos, glm::vec2 size, glm::vec4 color,float blurx,float blury)
{

	_Draw->DrawQuad(img, pos, size, color,blurx,blury);

}

void SynUI::DrawLine(Texture2D* img, glm::vec2 p1, glm::vec2 p2, glm::vec4 color,float width) {

	_Draw->DrawLine(img, p1, p2, color,width);

}
void SynUI::DrawStr(std::string text, glm::vec2 pos, glm::vec4 color)
{

	Theme->_Font->DrawTextUI(text, pos.x, pos.y,color);

}

int SynUI::StrW(std::string text) {

	return Theme->_Font->Width(text);

}

int SynUI::StrH(std::string text) {

	return Theme->_Font->Height() + 2;

}


IControl* SynUI::MouseOver(glm::vec2 pos)
{

	auto list = GetListBackward();

	for (auto const& control : list) {
		if (control == _RootControl) {
			continue;
		}
		if (control->InBounds(pos))
		{
			return control;
		}

	}
	
	return nullptr;

}