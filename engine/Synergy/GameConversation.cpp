#include "GameConversation.h"
#include "ConvNode.h"

GameConversation::GameConversation() {

}

void GameConversation::SetRoot(ConvNode* root) {

	_RootNode = root;

}

void GameConversation::SetTitle(std::string title) {

	_Title = title;

}

std::string GameConversation::GetTitle() {

	return _Title;

}