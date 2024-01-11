#include "Sample1_State.h"
#include <iostream>
#include "Texture2D.h"
#include "SmartDraw.h"
#include "SynApp.h"
#include "RndNum.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "Importer.h"
#include "Renderer.h"
#include "RenderQueue.h"
#include "QueueRenderScene.h"

void Sample1_State::InitState() {

	std::cout << "State initialized." << std::endl;
	_tex1 = new Texture2D("test/test1.png");
	_draw = new SmartDraw;
	_graph1 = new SceneGraph;
	_imp = new Importer;
	_ent1 = (Entity*)_imp->ImportNode("test/ent1.fbx");
	_render = new Renderer;
	_renderQueue = new RenderQueue;

	auto renderScene = new QueueRenderScene(_graph1);

	_renderQueue->AddNode(renderScene);

}

void Sample1_State::UpdateState() {

}

void Sample1_State::RenderState() {

	
	_draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());

	_render->Render(_renderQueue);


}