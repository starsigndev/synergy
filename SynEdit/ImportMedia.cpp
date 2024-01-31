#include "ImportMedia.h"
#include "IList.h"
#include "IWindowContent.h"
#include "GameResources.h"
#include "SynResources.h"
#include "Resource.h"
#include "ResourceGroup.h"
#include "IButton.h"
#include "Importer.h"
#include "SE_Global.h"
#include "SceneGraph.h"
#include "SynUI.h"

ImportMedia::ImportMedia() {
	_ResList = new IList;
	_Import = new IButton;
	SetPosition(glm::vec2(200, 200));
	SetSize(glm::vec2(500, 300));

	SetText("Import Resource");

	_Content->AddControl(_ResList);

	
	_Content->AddControl(_Import);
	_Import->SetSize(glm::vec2(100, 30));
	_Import->SetText("Import");

	_Import->OnClick = [&](IControl* c, void* d) {

		auto r_item = _ResList->GetActiveItem();
		auto res = (Resource*)r_item->Data;
		Importer* imp = new Importer;
		res->Load();
		auto node = imp->ImportNodeFromResource(res);

		SE_Global::_EditGraph->AddNode(node);

		SynUI::This->GetRootControl()->RemoveControl(this);

		};

}

void ImportMedia::SizeChanged() {

	IWindow::SizeChanged();
	_ResList->SetSize(glm::vec2(_Content->GetSize().x,_Content->GetSize().y-45));
	_Import->SetPosition(glm::vec2(10, _Content->GetSize().y - 38));



	auto res = GameResources::Resources->GetResources()->GetGroups();

	_ResList->Clear();

	for (auto const& g : res) {

		for (auto const& r : g->GetResources()) {

			auto item = _ResList->AddItem(r->GetName());
			item->Data = (void*)r;
		}
	}



}