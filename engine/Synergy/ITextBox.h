#pragma once
#include "IControl.h"


class ITextBox : public IControl
{
public:

	ITextBox();
	void Render();
	void TextChanged();
	int GetClaretX();
	void OnActivate();
	void OnDeactivate();
	void Update(float dt);
	std::string MaxString(std::string first);
	std::string GetString(std::string text, int start, int end);
private:

	bool _ClaretOn = true;
	int _ClaretX = 0;
	int _StartX = 0;
	int _NextClaret = 0;

	

};

