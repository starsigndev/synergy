#pragma once
#include "IWindow.h"

class IList;
class IButton;

class ImportMedia : public IWindow
{
public:

	ImportMedia();
	void SizeChanged();

private:
	IList* _ResList;
	IButton* _Import;
};

