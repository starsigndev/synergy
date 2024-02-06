#include "ConvEditor_Global.h"
#include "GameConversation.h"
#include "ConvNode.h"
#include "NewConversationWindow.h"
#include "SynUI.h"

GameConversation* ConvEditor_Global::_EditConv = nullptr;
ConvNode* ConvEditor_Global::_EditConvNode = nullptr;

void ConvEditor_Global::NewConv() {


	auto win = new NewConversationWindow;

	SynUI::This->SetTop(win);

	

	/*
	GameConversation* new_conv = new GameConversation;
	new_conv->SetTitle("New Conversation");
	ConvNode* root = new ConvNode;
	new_conv->SetRoot(root);
	*/

}