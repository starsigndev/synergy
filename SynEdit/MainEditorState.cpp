#include "MainEditorState.h"
#include "SynUI.h"

void MainEditorState::InitState() {

}

void MainEditorState::UpdateState(float dt) {
	_UI->UpdateUI(dt);
}

void MainEditorState::RenderState() {

	_UI->RenderUI();


}