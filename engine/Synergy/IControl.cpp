#include "IControl.h"
#include "IWindowDock.h"

IControl::IControl() {

	_Name = "Control1";
	_Image = nullptr;
	_RootControl = nullptr;
	_Color = glm::vec4(1, 1, 1, 1);
	//AddTag("NormalCursor");
}

glm::vec4 AddBounds(IControl* b,glm::vec4 wb) {

	auto bb = b->GetBounds();
	if (bb.x < wb.x)
	{
		wb.x = bb.x;
	}
	if (bb.y < wb.y) {
		wb.y = bb.y;
	}

	if (bb.z > wb.z) {
		wb.z = bb.z;
	}

	if (bb.w > wb.w)
	{
		wb.w = bb.w;
	}

	for (auto const& sub : b->GetControls())
	{
		wb = AddBounds(sub, wb);
	}

	return wb;


}

glm::vec4 IControl::WholeBounds() {

	auto b = AddBounds(this, glm::vec4(5000,5000, -50000,-50000));

	return b;

}

void IControl::SetPosition(glm::vec2 position) {

	_Position = position;
	PositionChanged();

}

void IControl::SetSize(glm::vec2 size) {

	_Size = size;
	SizeChanged();

}

IControl* IControl::GetDock() {

	IWindowDock* dock = dynamic_cast<IWindowDock*>(this);
	if (dock) {
		return this;
	}
	for (auto const& sub : _Controls) {

		auto res = sub->GetDock();
		if (res != nullptr) {
			return res;
		}
	}

	return nullptr;

}

void IControl::Set(glm::vec2 position, glm::vec2 size, std::string text)
{

	//SetPosition(position);
	//SetSize(size);
	_Position = position;
	_Size = size;
	_Text = text;
	PositionChanged();
	SizeChanged();
	TextChanged();

}

void IControl::SetImage(Texture2D* image) {

	_Image = image;

}

void IControl::SetText(std::string text) {

	_Text = text;
	TextChanged();

}

void IControl::RemoveControl(IControl* control) {
	_Controls.erase(std::remove(_Controls.begin(), _Controls.end(), control), _Controls.end());

}

void IControl::PositionChanged() {

}

void IControl::SizeChanged() {



}

glm::vec4 IControl::GetColor() {

	return _Color;

}

void IControl::SetColor(glm::vec4 color) {

	_Color = color;

}

glm::vec2 IControl::GetRenderPosition() {

	

	if (_RootControl != nullptr) {
		return _RootControl->GetRenderPosition() + _Position + _RootControl->GetScroll();
	}

	// If this control has no parent, its position is the render position
	return _Position;

}

glm::vec2 IControl::GetPosition() {

	return _Position;

}

glm::vec2 IControl::GetSize() {

	return _Size;

}

bool IControl::InBounds(glm::vec2 position) {

	auto rpos = GetRenderPosition();
	auto rsize = GetSize();

	if (position.x >= rpos.x && position.y >= rpos.y && position.x <= (rpos.x + rsize.x) && position.y <= (rpos.y + rsize.y)) {
		return true;
	}

	return false;

}

void IControl::Update(float dt) {

}

void IControl::Render() {


}

void IControl::AddControl(IControl* control) {

	_Controls.push_back(control);
	control->SetRootControl(this);

}

void IControl::InsertControl(IControl* control) {

	_Controls.insert(_Controls.begin(), control);


}

void IControl::InsertControl(IControl* control, int index)
{
	if (_Controls.size() <= index) {
		_Controls.push_back(control);
	}
	else {
		_Controls.insert(std::next(_Controls.begin(), index), control);
	}
}

void IControl::SetRootControl(IControl* control) {

	_RootControl = control;

}

IControl* IControl::GetRootControl() {

	return _RootControl;

}

std::vector<IControl*> IControl::GetControls() {

	return _Controls;

}

bool IControl::HasControl(IControl* control) {

	for (auto const& con : _Controls) {
		
		if (con == control) return true;

	}

	return false;
}