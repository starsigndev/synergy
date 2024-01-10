#include "Sample1App.h"
#include "Sample1_State.h"

Sample1App::Sample1App() : SynApp(1024, 768, "Sample 1", false)
{
	
	PushState(new Sample1_State);

};