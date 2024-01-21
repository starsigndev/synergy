#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <functional>
class Texture2D;

class IControl
{
public:

	IControl();
	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 size);
	void Set(glm::vec2 position, glm::vec2 size, std::string text);
	void SetImage(Texture2D* image);
	void SetText(std::string text);
	glm::vec2 GetRenderPosition();
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);
	virtual bool InBounds(glm::vec2 position);
	virtual void SizeChanged();
	virtual void PositionChanged();
	virtual void TextChanged() {};
	virtual void Update(float dt);
	virtual void Render();
	virtual void OnKey(int key) {};
	void AddControl(IControl* control);
	void SetRootControl(IControl* control);
	IControl* GetRootControl();
	std::vector<IControl*> GetControls();
	void RemoveControl(IControl* control);
	virtual void OnMouseEnter() {};
	virtual void OnMouseLeave() {};
	virtual void OnMouseDown(int button) {};
	virtual void OnMouseUp(int button) {};
	virtual void OnMouseDrag(glm::vec2 pos,glm::vec2 delta) {};
	virtual void OnMouseMove(glm::vec2 pos, glm::vec2 delta) {};
	virtual void OnActivate() {};
	virtual void OnDeactivate() {};
	virtual void SetShift(bool shift) {};
	virtual void SetScroll(glm::vec2 scroll)
	{
		_Scroll = scroll;
	}
	virtual glm::vec2 GetScroll() {
		return _Scroll;
	}
	void SetScissor(glm::vec4 scissor) {
		_Scissor = scissor;
	}
	glm::vec4 GetScissor() {
		return _Scissor;
	}

	std::function<void()> OnClick;
	std::function<void(glm::vec2)> OnDrag;
	std::function<void(float value)> OnValueChanged;

protected:

	glm::vec2 _Position = glm::vec2(0, 0);
	glm::vec2 _Size = glm::vec2(0, 0);
	std::string _Name = "";
	std::string _Text = "";
	glm::vec2 _Scroll = glm::vec2(0, 0);
	Texture2D* _Image;
	glm::vec4 _Color = glm::vec4(1, 1, 1, 0.8f);
	std::vector<IControl*> _Controls;
	IControl* _RootControl;
	bool _Active = false;
	glm::vec4 _Scissor = glm::vec4(-1, -1, -1, -1);

};

