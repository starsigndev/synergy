#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "IControl.h"

class SmartDraw;
class Texture2D;
class ITheme;

class SynUI

{
public:

	SynUI();
	void AddControl(IControl* control);
	IControl* GetRootControl();
	void UpdateUI(float dt);
	void RenderUI();
	void RenderList(std::vector<IControl*> controls);
	std::vector<IControl*> GetListForward();
	std::vector<IControl*> GetListBackward();
	std::vector<IControl*> AddControlToList(std::vector<IControl*>, IControl* control);
	void UpdateMouse();
	void UpdateKB();
	IControl* MouseOver(glm::vec2 position);

	//
	void DrawCursor();
	static SmartDraw* _Draw;

	static ITheme* Theme;
	static void Draw(Texture2D* img, glm::vec2 pos, glm::vec2 sizze, glm::vec4 col);
	static void DrawStr(std::string text, glm::vec2(pos), glm::vec4 color);
	static int StrW(std::string text);
	static int StrH(std::string text);
private:

	IControl* _RootControl = nullptr;

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
	int _CurrentKey = -1;
	bool _FirstKey = true;
	int _NextKey = 0;

};

