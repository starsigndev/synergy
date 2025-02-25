#include "ITreeView.h"
#include "IVScroller.h"
#include "SynUI.h"
#include "ITheme.h"
#include "SmartDraw.h"

ITreeView::ITreeView() {

	_VScroller = new IVScroller;
	AddControl(_VScroller);
	_RootItem = new TreeItem("Root");
	_RootItem->Text = "Root";
	_Outline = false;
	_RootItem->Open = true;
	_ScissorTest = true;
}

void ITreeView::SizeChanged() {

	_VScroller->SetPosition(glm::vec2(_Size.x - 15, 0));
	_VScroller->SetSize(glm::vec2(15, _Size.y));

}

void ITreeView::AddItem(TreeItem* item) {

	_RootItem->Items.push_back(item);

}

TreeItem* ITreeView::AddItem(std::string text, void* data)
{

	TreeItem* item = new TreeItem(text, data);
	_RootItem->Items.push_back(item);
	return item;

}

int ITreeView::CheckItem(TreeItem* item, int dx, int dy,glm::vec2 pos) {


	if (!item->Disabled) {
		if (pos.y >= dy && pos.y <= dy + 28) {

			_OverItem = item;
			return dy + 28;

		}

	}
	else {
		dy = dy - 26;
		dx = dx - 25;
	}

	if (item->Open)
	{

		for (auto const& sub : item->Items)
		{
			dy = CheckItem(sub, dx + 20, dy + 26,pos);
		}

	}

	return dy;

}

void ITreeView::OnMouseMove(glm::vec2 pos, glm::vec2 delta) {

	int sv = (int)((float)_MaxY * _VScroller->GetValue());
	_OverItem = nullptr;
	CheckItem(_RootItem,5 ,5-sv,pos);

}

void ITreeView::OnMouseDown(int button) {
	if (button != 0) return;
	if (_OverItem) {

		_OverItem->Open = _OverItem->Open ? false : true;

		_ActiveItem = _OverItem;

		if (_OverItem->ItemSelected) {

			_OverItem->ItemSelected(_OverItem);

		}

	}

}

void ITreeView::Render() {
	int sv = (int)((float)_MaxY * _VScroller->GetValue());

	auto pos = GetRenderPosition();

//	SynUI::_Draw->End();
//	SynUI::_Draw->Begin();
//	SynUI::_Draw->SetScissor(glm::vec4(pos.x, pos.y, _Size.x, _Size.y));
	//SynUI::_Draw->SetScissor(glm::vec4(pos.x, pos.y, _Size.x-15, _Size.y));
	//SynUI::Draw(SynUI::Theme->_DarkFrame, pos, GetSize(), glm::vec4(1, 1, 1, 1));
	_MaxY = RenderItem(_RootItem, pos.x + 5, pos.y + 5 - sv) + sv;
	//SynUI::_Draw->SetScissor(glm::vec4(-1, -1, -1, -1));

//	SynUI::_Draw->End();
//	SynUI::_Draw->ResetScissor();
//	SynUI::_Draw->Begin();
}

int ITreeView::RenderItem(TreeItem* item, int dx, int dy)
{

	//y = dy - (int)((float)_MaxY * _VScroller->GetValue());
	if (item->Disabled == false) {
		if (item == _OverItem)
		{
			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(GetRenderPosition().x, dy), glm::vec2(_Size.x, 22), glm::vec4(0, 2, 2, 1.0f));
		}

		if (item == _ActiveItem) {
			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(GetRenderPosition().x, dy), glm::vec2(_Size.x, 22), glm::vec4(0, 2, 0, 1.0f));
		}

		if (item->Items.size() > 0) {
			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(dx - 1, dy + 2), glm::vec2(18, 18), glm::vec4(4.8f, 4.8f, 4.8f, 1.0f));
			SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(dx, dy + 3), glm::vec2(16, 16), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
			if (item->Open) {
				SynUI::Draw(SynUI::Theme->_Frame, glm::vec2(dx + 3, dy + 6), glm::vec2(10, 10), glm::vec4(3, 3, 3, 1));
			}
		}


		SynUI::DrawStr(item->Text, glm::vec2(dx + 25, dy + 1), glm::vec4(1, 1, 1, 1));

	}
	else {
		dy = dy - 26;
		dx = dx - 25;
	}

	if (item->Open)
	{

		for (auto const& sub : item->Items)
		{
			dy = RenderItem(sub, dx + 25, dy+26);
		}

	}

	return dy;

}

void ITreeView::Update(float dt) {

	_VScroller->SetMaxValue(_MaxY);


}

TreeItem* ITreeView::GetActiveItem() {

	return _ActiveItem;

}

DragInfo ITreeView::BeginDrag() {

	DragInfo info;

	if (_OverItem) {
		info.Accepted = true;
		info.Text = _OverItem->Text;
		info.Data1 = _OverItem;
		info.From = this;
		return info;
	}
	info.Accepted = false;
	return info;
}

void ITreeView::DragOver(DragInfo info) {

}

void ITreeView::CompleteDrag(DragInfo info)
{
	if (info.From == this) {
		
		auto ditem = (TreeItem*)info.Data1;
		if (ditem == _OverItem) return;
		if (_OverItem) {
			if (_OverItem->Contains(ditem)) {
				return;
			}
			_OverItem->Items.push_back(ditem);
		
			if (ditem->Root)
			{
				ditem->Root->RemoveItem(ditem);
				// Find the item in the vector
				

			}
			ditem->Root = _OverItem;
			//ditem->Root->Items.erase()

		}
	}
	
}