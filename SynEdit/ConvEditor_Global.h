#pragma once

class GameConversation;
class ConvNode;

class ConvEditor_Global
{
public:
	static GameConversation* _EditConv;
	static ConvNode* _EditConvNode;
	static void NewConv();
};

