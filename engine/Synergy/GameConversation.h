#pragma once
#include <string>

class ConvNode;

class GameConversation
{
public:

	GameConversation();
	void SetRoot(ConvNode* node);
	void SetTitle(std::string title);
	std::string GetTitle();

private:

	std::string _Title;
	ConvNode* _RootNode;

};

