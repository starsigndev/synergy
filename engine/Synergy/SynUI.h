#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "IControl.h"


class SmartDraw;
class Texture2D;
class IMenuBar;
class ITheme;
class IWindowDock;
class IToolbar;

class SynUI

{
public:

	SynUI();
	void AddControl(IControl* control);
	IControl* GetRootControl();
	void UpdateUI(float dt);
	IWindowDock* GetDock();
	void RenderUI();
	void RenderControl(IControl* control);
	void RenderList(std::vector<IControl*> controls);
	std::vector<IControl*> GetListForward();
	std::vector<IControl*> GetListBackward();
	std::vector<IControl*> AddControlToList(std::vector<IControl*>, IControl* control);
	IControl* ControlBeneath(IControl* control);
	void UpdateMouse();
	void UpdateKB();
	IControl* MouseOver(glm::vec2 position);
	IMenuBar* GetMenuBar() {
		return _MenuBar;
	}
	IToolbar* GetToolbar() {
		return _Toolbar;
	}
	//
	void DrawCursor();
	static SmartDraw* _Draw;

	static ITheme* Theme;
	static void DrawLine(Texture2D* img, glm::vec2 p1, glm::vec2 p2, glm::vec4 col,float width=1.0);
	static void Draw(Texture2D* img, glm::vec2 pos, glm::vec2 sizze, glm::vec4 col, float blurx = 0,float blury=0);
	static void Draw(Texture2D* img, glm::vec2 pos, glm::vec2 sizze, glm::vec4 uv,glm::vec4 col,float blurx=0,float blury=0);
	static void Draw(Texture2D* img, glm::vec2 pos, glm::vec2 size, glm::vec4 u, glm::vec4 v, glm::vec4 color, float blurx = 0, float blury = 0);
	static void DrawStr(std::string text, glm::vec2(pos), glm::vec4 color);

	static int StrW(std::string text);
	static int StrH(std::string text);
	void Resize(int w, int h);
	IWindow* RootWindow(IControl* c);
	void AddToIgnore(IControl* control);
	bool Ignored(IControl* control);
	IControl* GetOver() {
		return _Over;
	}
	static SynUI* This;

	void SetTop(IControl* control) {
		_TopControl = control;
	}
private:

	IControl* _RootControl = nullptr;
	IControl* _TopControl = nullptr;
	IWindowDock* _WindowDock = nullptr;
	IMenuBar* _MenuBar = nullptr;
	IToolbar* _Toolbar;

	//mouse
	glm::vec2 _MousePosition;
	glm::vec2 _MouseDelta;
	bool _MouseButton[16];

	//cursor
	Texture2D* _Cursor;

	//state
	IControl* _Over = nullptr;
	IControl* _Pressed = nullptr;
	IControl* _Active = nullptr;
	IControl* _WindowOver = nullptr;
	IControl* _WindowBelow = nullptr;

	Texture2D* _WhiteTex = nullptr;

	std::vector<IControl*> _Ignore;


	int _CurrentKey = -1;
	bool _FirstKey = true;
	int _NextKey = 0;



};

