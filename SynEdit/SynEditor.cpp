#include "SynEditor.h"
//#include "MainEditorState.h"
#include "GeneralOSState.h"
#include "GameResources.h"

SynEditor::SynEditor() : SynApp(1800, 900, "SynEditor", false)
{

	Resources = new GameResources("");


	PushState(new GeneralOSState);

};