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
	void OnKey(int key);
	std::string GetChr(int key);
	std::string MaxString(std::string first);
	int MaxChars();
	std::string GetString(std::string text, int start, int end);
	void SetShift(bool shift) {
		_ShiftOn = shift;
	}
private:

	bool _ShiftOn = false;
	bool _ClaretOn = true;
	int _ClaretX = 0;
	int _StartX = 0;
	int _NextClaret = 0;
	int _DisLen = 0;

	

};

