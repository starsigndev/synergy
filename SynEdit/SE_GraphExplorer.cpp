#include "SE_GraphExplorer.h"
#include "ITextBox.h"
#include "IWindowContent.h"
#include "ITreeView.h"
#include "SE_Global.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include <iostream>
#include <algorithm>
#include <cctype>
SE_GraphExplorer* SE_GraphExplorer::This = nullptr;

SE_GraphExplorer::SE_GraphExplorer() {
	
	This = this;
	_SearchBox = new ITextBox;
	_Content->AddControl(_SearchBox);
	SetText("Scene Explorer");
	_SearchBox->SetGuideText("Enter search words...");

	_SceneTree = new ITreeView;

	_SceneTree->GetRootItem()->Text = "Scene";

	_Content->AddControl(_SceneTree);

	
	_SearchBox->OnChanged = [&](std::string term) {

		if (term == "" || term == " ") {
			SearchDisable();

		}
		else {
			SearchFor(term);
		}

		};

}

void SE_GraphExplorer::SizeChanged() {

	IWindow::SizeChanged();

	_SearchBox->Set(glm::vec2(0, 0), glm::vec2(_Content->GetSize().x, 30), "");
	_SceneTree->Set(glm::vec2(0, 32), glm::vec2(_Content->GetSize().x, _Content->GetSize().y - 35),"");

}

void SE_GraphExplorer::RebuildUI() {

	if (_SearchBox->GetText() == "") {
		SearchDisable();
	
	}
	else {
		SearchFor(_SearchBox->GetText());
	}
}

void SE_GraphExplorer::AddNodes(TreeItem* item, Node3D* node)
{

	item->Text = node->GetName();
	item->Data = node;
	item->Disabled = false;

	for (auto const& sub : node->GetNodes()) {

		TreeItem* sub_item = item->AddItem("");
		AddNodes(sub_item, sub);

	};

}

bool containsIgnoreCase2(const std::string& search_string, const std::string& search_for) {
	// Convert both strings to lowercase for case-insensitive comparison
	std::string search_string_lower = search_string;
	std::transform(search_string_lower.begin(), search_string_lower.end(), search_string_lower.begin(), ::tolower);

	std::string search_for_lower = search_for;
	std::transform(search_for_lower.begin(), search_for_lower.end(), search_for_lower.begin(), ::tolower);

	// Check if search_for is contained within search_string
	return search_string_lower.find(search_for_lower) != std::string::npos;
}

void SE_GraphExplorer::AddNodesSearch(TreeItem* item, Node3D* node,std::string term)
{

	item->Text = node->GetName();

	for (auto const& sub : node->GetNodes()) {

		if (containsIgnoreCase2(sub->GetName(), term)) {
			TreeItem* sub_item = item->AddItem("");

			AddNodesSearch(sub_item, sub,term);
		}
		else {
			AddNodesSearch(item, sub, term);
		}
	};

}

void SE_GraphExplorer::SearchDisable() {
	auto root = _SceneTree->GetRootItem();
	root->Items.clear();

	AddNodes(root, SE_Global::_EditGraph->GetRootNode());
}

void SE_GraphExplorer::SearchFor(std::string term) {

	auto root = _SceneTree->GetRootItem();
	root->Items.clear();
	
	AddNodes(root, SE_Global::_EditGraph->GetRootNode());

	DisableNodes(root, term);

}

void SE_GraphExplorer::DisableNodes(TreeItem* item, std::string term) {

	if (!containsIgnoreCase2(item->Text, term))
	{
		item->Disabled = true;
	}
	else {
		item->Disabled = false;
	}

	for (auto const& sub : item->Items) {
		DisableNodes(sub, term);
	}
}