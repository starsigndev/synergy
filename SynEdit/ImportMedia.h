#pragma once
#include "IWindow.h"

class IList;
class IButton;
class ITextBox;

class ImportMedia : public IWindow
{
public:

	ImportMedia();
	void SizeChanged();
	void SearchFor(std::string);
	void SearchDisable();

private:
	IList* _ResList;
	IButton* _Import;
	ITextBox* _SearchBox;
};

