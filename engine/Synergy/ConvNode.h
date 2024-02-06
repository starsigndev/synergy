#pragma once
#include <vector>
#include <string>

class ConvNode
{
public:

	ConvNode();
	void SetSpeaker(std::string name);
	void SetSpeech(std::string text);
	void AddResponse(ConvNode* response);
	std::vector<ConvNode*> GetResponses();

private:

	std::string _Speaker;
	std::string _SpeechText;

	std::vector<ConvNode*> _Responses;

};

