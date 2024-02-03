#include "SE_Viewer.h"
#include "RenderTarget2D.h"
#include "IWindowContent.h"
#include "IImage.h"
#include "SceneGraph.h"
#include "RenderQueue.h"
#include "Renderer.h"
#include "Camera.h"
#include "QueueSetCamera.h"
#include "QueueSetLights.h"
#include "QueueRenderScene.h"
#include "QueueRenderShadows.h"
#include "QueueBindRenderTarget2D.h"
#include "QueueReleaseRenderTarget2D.h"
#include "QueueRenderPostProcess.h"
#include "QueuePresentRenderTarget.h"
#include "QueueRenderMeshLines.h"
#include "Light.h"
#include "MeshLines.h"
#include "AppInput.h"
#include "SE_Global.h"
#include "SE_Viewport.h"
#include "Importer.h"
#include "Node3D.h"
#include "Entity.h"

SE_Viewer::SE_Viewer() {
	
	
	SetText("Scene Viewer");
	RemoveControl(_Content);
	_Content = new SE_Viewport;

	_Content->SetPosition(glm::vec2(0, 21));
	AddControl(_Content);
	SizeChanged();
	


}

void SE_Viewer::SizeChanged() {

	IWindow::SizeChanged();

	

}

void SE_Viewer::PreRender() {

	

	//	_RT->Bind();

		//_RT->Release();


}

void SE_Viewer::Update(float dt) {

	

}