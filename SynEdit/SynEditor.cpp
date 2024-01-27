#include "SynEditor.h"
//#include "MainEditorState.h"
#include "GeneralOSState.h"

SynEditor::SynEditor() : SynApp(1800, 900, "SynEditor", false)
{

	PushState(new GeneralOSState);

};