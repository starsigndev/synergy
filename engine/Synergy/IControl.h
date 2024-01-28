#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <map>
#include <string>
#include <functional>
class Texture2D;
class IWindow;

class IControl
{
public:

	IControl();
	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 size);
	void Set(glm::vec2 position, glm::vec2 size, std::string text);
	void SetImage(Texture2D* image);
	void SetText(std::string text);
	std::string GetText() {
		return _Text;
	}
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
	virtual void WindowOver(IWindow* window) {};
	virtual void WindowDropped(IWindow* window) {}
	void AddControl(IControl* control);
	IControl* GetDock();
	void InsertControl(IControl* control);
	void InsertControl(IControl* control,int index);
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


	void SetOutline(bool outline) {
		_Outline = outline;
	}
	bool GetOutline() {
		return _Outline;
	}
	void AddTag(std::string tag,std::string value) {
		_Tags[tag] = value;
	}

	std::map<std::string,std::string> GetTags() {
		return _Tags;
	}

	std::string GetTagValue(std::string tag) {

		return _Tags[tag];

	}

	bool HasTag(std::string tag) {

		if (_Tags.find(tag) != _Tags.end()) {
			// Key exists
			return true;
		}
		else {
			return false;
			// Key does not exist
		}
		return false;
	}

	void RemoveTag(std::string tag) {
		
		_Tags.erase(tag);


		//_Tags.erase(std::remove(_Tags.begin(), _Tags.end(), tag), _Tags.end());


	}

	glm::vec4 GetBounds() {

		return glm::vec4(GetRenderPosition().x, GetRenderPosition().y, GetSize().x, GetSize().y);

	}

	glm::vec4 WholeBounds();

	bool GetScissor() {
		return _ScissorTest;
	}
	bool GetWholeScissor() {
		return _WholeScissor;
	}
	void SetScissor(bool enable) {
		_ScissorTest = true;
	}

	std::function<void(IControl*,void*data)> OnClick;
	std::function<void(glm::vec2)> OnDrag;
	std::function<void(float value)> OnValueChanged;
	bool CanActivate() {
		return _CanActivate;
	}
	bool ScissorChildren() {
		return _ScissorChildren;
	}
	Texture2D* GetOutlineImage() {
		return _OutlineImage;
	}
	void SetOutlineImage(Texture2D* image) {
		_OutlineImage = image;
	}
	bool HasControl(IControl* control);
	void SetUV(glm::vec4 uv) {
		_UV = uv;
	}
	void Expand();
protected:

	bool _CanActivate = true;
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
	bool _Outline = true;
	std::map<std::string,std::string> _Tags;
	Texture2D* _OutlineImage = nullptr;
	glm::vec4 _UV;
	bool _ScissorChildren = true;
	bool _ScissorTest = false;
	bool _WholeScissor = false;
	void* _Data;
};

