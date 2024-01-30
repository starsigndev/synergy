#include "SE_GraphExplorer.h"
#include "ITextBox.h"
#include "IWindowContent.h"
#include "ITreeView.h"

SE_GraphExplorer::SE_GraphExplorer() {
	
	_SearchBar = new ITextBox;
	_Content->AddControl(_SearchBar);
	SetText("Scene Explorer");
	_SearchBar->SetGuideText("Enter search words...");

	_SceneTree = new ITreeView;

	_SceneTree->GetRootItem()->Text = "Scene";

	_Content->AddControl(_SceneTree);


}

void SE_GraphExplorer::SizeChanged() {

	IWindow::SizeChanged();

	_SearchBar->Set(glm::vec2(0, 0), glm::vec2(_Content->GetSize().x, 30), "");
	_SceneTree->Set(glm::vec2(0, 32), glm::vec2(_Content->GetSize().x, _Content->GetSize().y - 35),"");

}