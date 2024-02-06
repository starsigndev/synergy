#include "ConvNode.h"

ConvNode::ConvNode() {

}

void ConvNode::SetSpeaker(std::string name) {

	_Speaker = name;

}

void ConvNode::SetSpeech(std::string text) {

	_SpeechText = text;

}

void ConvNode::AddResponse(ConvNode* response) {

	_Responses.push_back(response);

}

std::vector<ConvNode*> ConvNode::GetResponses() {

	return _Responses;

}