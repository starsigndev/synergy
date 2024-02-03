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
#include "ITextBox.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include "SE_GraphExplorer.h"

ImportMedia::ImportMedia() {
	_ResList = new IList;
	_Import = new IButton;
	_SearchBox = new ITextBox;
	_SearchBox->SetGuideText("Enter search terms...");

	//Search Box---------------------------------------------------


	_SearchBox->OnChanged = [&](std::string term) {

		if (term == "" || term == " "){
			SearchDisable();

		}
		else {
			SearchFor(term);
		}

		};

	SetPosition(glm::vec2(200, 200));
	SetSize(glm::vec2(500, 300));

	SetText("Import Resource");

	_Content->AddControl(_ResList);
	_Content->AddControl(_SearchBox);
	
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

		SE_GraphExplorer::This->RebuildUI();


		};
	SearchDisable();
}

void ImportMedia::SizeChanged() {

	IWindow::SizeChanged();
	_ResList->SetPosition(glm::vec2(0, 32));
	_ResList->SetSize(glm::vec2(_Content->GetSize().x,_Content->GetSize().y-77));
	_Import->SetPosition(glm::vec2(8, _Content->GetSize().y - 36));
	_SearchBox->SetSize(glm::vec2(_Content->GetSize().x, 30));



	auto res = GameResources::Resources->GetResources()->GetGroups();

	_ResList->Clear();

	for (auto const& g : res) {

		for (auto const& r : g->GetResources()) {

			auto item = _ResList->AddItem(r->GetName());
			item->Data = (void*)r;
		}
	}



}

bool containsIgnoreCase(const std::string& search_string, const std::string& search_for) {
	// Convert both strings to lowercase for case-insensitive comparison
	std::string search_string_lower = search_string;
	std::transform(search_string_lower.begin(), search_string_lower.end(), search_string_lower.begin(), ::tolower);

	std::string search_for_lower = search_for;
	std::transform(search_for_lower.begin(), search_for_lower.end(), search_for_lower.begin(), ::tolower);

	// Check if search_for is contained within search_string
	return search_string_lower.find(search_for_lower) != std::string::npos;
}

void ImportMedia::SearchFor(std::string term)
{
	auto res = GameResources::Resources->GetResources()->GetGroups();

	_ResList->Clear();

	for (auto const& g : res) {

		for (auto const& r : g->GetResources()) {
			if (containsIgnoreCase(r->GetName(), "fbx") ){
				if (containsIgnoreCase(r->GetName(), term)) {
					auto item = _ResList->AddItem(r->GetName());
					item->Data = (void*)r;
				}
			}
		}
	}

}

void ImportMedia::SearchDisable() {

	auto res = GameResources::Resources->GetResources()->GetGroups();

	_ResList->Clear();

	for (auto const& g : res) {

		for (auto const& r : g->GetResources()) {


			if (containsIgnoreCase(r->GetName(), "fbx")) {
				auto item = _ResList->AddItem(r->GetName());
				item->Data = (void*)r;
			}
		}
	}


}