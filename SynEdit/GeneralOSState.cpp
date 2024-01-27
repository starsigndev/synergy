#include "GeneralOSState.h"
#include "SynUI.h"

void GeneralOSState::InitState() {

}

void GeneralOSState::UpdateState(float dt) {
	_UI->UpdateUI(dt);
}

void GeneralOSState::RenderState() {

	_UI->RenderUI();


}