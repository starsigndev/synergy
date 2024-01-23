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

class SynUI

{
public:

	SynUI();
	void AddControl(IControl* control);
	IControl* GetRootControl();
	void UpdateUI(float dt);
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
	//
	void DrawCursor();
	static SmartDraw* _Draw;

	static ITheme* Theme;
	static void Draw(Texture2D* img, glm::vec2 pos, glm::vec2 sizze, glm::vec4 col);
	static void DrawStr(std::string text, glm::vec2(pos), glm::vec4 color);
	static int StrW(std::string text);
	static int StrH(std::string text);
	void Resize(int w, int h);
	IWindow* RootWindow(IControl* c);
	void AddToIgnore(IControl* control);
	bool Ignored(IControl* control);

	static SynUI* This;


private:

	IControl* _RootControl = nullptr;
	IWindowDock* _WindowDock = nullptr;
	IMenuBar* _MenuBar = nullptr;

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

	std::vector<IControl*> _Ignore;


	int _CurrentKey = -1;
	bool _FirstKey = true;
	int _NextKey = 0;



};

