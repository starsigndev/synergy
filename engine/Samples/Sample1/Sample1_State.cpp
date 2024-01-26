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
#include "QueueSetCamera.h"
#include "QueueSetLights.h"
#include "QueueRenderScene.h"
#include "QueueRenderShadows.h"
#include "Light.h"
#include "Camera.h"
#include "Actor.h"
#include "QueueBindRenderTarget2D.h"
#include "QueueReleaseRenderTarget2D.h"
#include "QueueRenderPostProcess.h"
#include "QueuePresentRenderTarget.h"
#include "AppInput.h"
#include "PPBloom.h"
#include "PPDepthOfField.h"
#include "ThemeArc.h"
#include "SynUI.h"
#include "IControl.h"
#include "IButton.h"
#include "IWindow.h"
#include "IFrame.h"
#include "ITextBox.h"
#include "ITreeView.h"
#include "IMenuBar.h"
#include "IWindowContent.h"
#include "IWindowDock.h"
#include "IList.h"
#include "IDial.h"
#include "ISelector.h"
#include "IToolbar.h"
#include "ITheme.h"
#include "IImage.h"
#include "INumeric.h"
#include "IAngleSelect.h"
#include "ILabel.h"
#include "IProgressBar.h"
#include "IToggle.h" 
#include "IDropButtons.h"
#include "IVectorList.h"

glm::vec3 rot;

glm::vec3 cam_rot;
PPBloom* _ppBloom;

void Sample1_State::InitState() {

	cam_rot = glm::vec3(0, 0, 0);
	std::cout << "State initialized." << std::endl;
	_tex1 = new Texture2D("test/test1.png");
	_draw = new SmartDraw;
	_graph1 = new SceneGraph;
	_imp = new Importer;
	_ent1 = (Entity*)_imp->ImportNode("test/ent1.fbx");
	_act1 = (Actor*)_imp->ImportActor("test/walk1.fbx");
	_render = new Renderer;
	_renderQueue = new RenderQueue;
	_graph1->AddNode(_ent1);
	_graph1->AddNode(_act1);
	_act1->SetScale(glm::vec3(0.02f, 0.02f, 0.02f));

	_render->SetGraph(_graph1);

	_light1 = new Light;
	auto _light2 = new Light;


	_light1->SetPosition(glm::vec3(0, 10, 4));
	_light2->SetPosition(glm::vec3(2, 10, -10));

	_lights1.push_back(_light1);
	//_lights1.push_back(_light2);


	_cam1 = new Camera;

	_light1->SetDiffuseColor(glm::vec3(1, 1, 1));
	_light2->SetDiffuseColor(glm::vec3(1, 3, 3));

	_rt1 = new RenderTarget2D(SynApp::This->GetWidth(), SynApp::This->GetHeight());
	_ppBloom = new PPBloom();
	auto _ppDOF = new PPDepthOfField();

	auto setCamera = new QueueSetCamera(_cam1);
	auto setLights = new QueueSetLights(_lights1);
	auto renderScene = new QueueRenderScene(_graph1);
	auto renderShadows = new QueueRenderShadows(_graph1);
	auto bindRT = new QueueBindRenderTarget2D(_rt1);
	auto relRT = new QueueReleaseRenderTarget2D(_rt1);
	auto renPP = new QueueRenderPostProcess(_rt1, _ppDOF);
	auto pRT = new QueuePresentRenderTarget(_ppDOF->GetOutput());

	_renderQueue->AddNode(setCamera);
	_renderQueue->AddNode(setLights);
	_renderQueue->AddNode(renderShadows);
	_renderQueue->AddNode(bindRT);
	_renderQueue->AddNode(renderScene);
	_renderQueue->AddNode(relRT);
	_renderQueue->AddNode(renPP);
	_renderQueue->AddNode(pRT);




	_cam1->SetPosition(glm::vec3(0, 0, 10));

	rot = glm::vec3(0, 0, 0);

	_ui1 = new SynUI;
	
//	auto icon = new Texture2D("ui/icon/synergyicon.png"); auto menu = _ui1->GetMenuBar();
//	menu->SetIcon(icon);


	auto root = _ui1->GetRootControl();

	auto win1 = new IWindow(false);
	win1->Set(glm::vec2(60, 60), glm::vec2(300, 400), "Window");
//	_ui1->AddControl(win1);

	auto win2 = new IWindow(false);
	win2->Set(glm::vec2(160, 260), glm::vec2(300, 400), "Games");
//	_ui1->AddControl(win2);

	auto win3 = new IWindow(true);
	win3->Set(glm::vec2(60, 360), glm::vec2(300, 400), "Tools");
	//_ui1->AddControl(win3);

	auto win4 = new IWindow(true);
	win4->Set(glm::vec2(20, 360), glm::vec2(300, 400), "Tools");
	//_ui1->AddControl(win4);

	
	auto win41 = new IWindow(true);
	win41->Set(glm::vec2(60, 60), glm::vec2(300, 400), "Window");

	auto tb1 = new ITextBox;
	tb1->Set(glm::vec2(20, 100), glm::vec2(190, 30), "");
	//tb1->SetNumeric(true);
	tb1->SetPassword(true);

	//auto nb1 = new INumeric;
	//nb1->SetPosition(glm::vec2(50, 50));
	auto nb1 = new IDial;
	nb1->Set(glm::vec2(40, 40), glm::vec2(128,128), "");

	//auto as = new IAngleSelect;
	//as->Set(glm::vec2(180, 50), glm::vec2(128, 128), "");

	auto as = new IProgressBar;
	as->Set(glm::vec2(180, 50), glm::vec2(200, 30), "");

	std::vector<float> test;
	test.push_back(5);
	test.push_back(25);
	test.push_back(50);

	std::vector<Node3D*> nodes;
	nodes.push_back(_ent1);


	auto t1 = new IVectorList<float>("Float");
	t1->Set(glm::vec2(20, 20), glm::vec2(120, 30), "");
	//t1->SetLabel("GLSL?");
	t1->SetList(test);



	auto but1 = new IButton();
	//win41->GetContent()->AddControl(but1);
	//win41->GetContent()->AddControl(nb1);
	win41->GetContent()->AddControl(t1);

	auto tv = new ITreeView;
	tv->Set(glm::vec2(0, 0), glm::vec2(200, 768), "");

	TreeItem* i1 = new TreeItem("Scene");
	TreeItem* i2 = new TreeItem("Lights");
	TreeItem* i3 = new TreeItem("Cameras");

	tv->AddItem(i1);
	tv->AddItem(i2);
	tv->AddItem(i3);

	i1->AddItem("Map");
	i1->AddItem("Walls");

	i2->AddItem("Light 1");
	i2->AddItem("Cinematic Light 1");


	for (int i = 0; i < 300; i++) {
		i3->AddItem("Camera 1");
		i3->AddItem("Cinematic Camera 222222221");
	}


	but1->Set(glm::vec2(20, 400), glm::vec2(100,25), "Testing");
//	_ui1->GetRootControl()->AddControl(tv);
	_ui1->GetRootControl()->AddControl(win41);

	auto l1 = new ISelector;
	
	l1->AddItems({ "DirectX","OpenGL","Vulkan","Metal","DirectX11" });

	l1->ItemSelected = [](ListItem* item) {

		std::cout << "List:" << item->Text << std::endl;

		};

	l1->Set(glm::vec2(30, 230), glm::vec2(200, 30), "");

	win41->GetContent()->AddControl(l1);

	auto img = new IImage(SynUI::Theme->_NewScene);
	img->SetPosition(glm::vec2(60, 40));
	img->SetSize(glm::vec2(128, 128));
	//win41->GetContent()->AddControl(img);

	auto lab = new ILabel("Image");
	lab->SetPosition(glm::vec2(5, 100));
	//win41->GetContent()->AddControl(lab);



	but1->OnClick = [](IControl* c,void* data) {

	//	exit(1);

		};


	auto menu = _ui1->GetMenuBar();

	auto icon = new Texture2D("ui/icon/synergyicon.png");

	menu->SetIcon(icon);

	auto file_menu = menu->AddItem("File");
	menu->AddItem("Edit");
	menu->AddItem("Windows");
	menu->AddItem("Help");

	auto it = file_menu->AddItem("Load Project");

	it->SetIcon(SynUI::Theme->_NewScene);

	auto save = file_menu->AddItem("Save Project");
	file_menu->AddItem("Close Project");
	file_menu->AddItem("Settings");
	auto close_ed = file_menu->AddItem("Close Editor");
	close_ed->OnClick = [&]() {

		exit(1);

		};

	save->AddItem("Save whole project");
	auto dif = save->AddItem("Save difference project");
	save->AddItem("Save streaming world.");
	dif->AddItem("Save progressive differences.");
	dif->AddItem("Save non-progressive differences");
	//*/

	auto tool = _ui1->GetToolbar();
	auto trans = tool->AddButton(SynUI::Theme->_Translate);
	tool->AddButton(SynUI::Theme->_Rotate);
	tool->AddButton(SynUI::Theme->_Scale);
	trans->SetOutline(true);

	auto db1 = new IDropButtons("Space");
	db1->AddItem("Local");
	db1->AddItem("Global");
	db1->AddItem("SmartSpace");
	tool->Add(db1);

	auto s1 = new ISelector;
	s1->SetSize(glm::vec2(120, 25));
	s1->AddItems({ "Translate","Rotate","Scale" });

	//s1->AddItem("Translate");
	//s1->AddItem("Rotate");
	//s1->AddItem("Scale");

	tool->Add(s1);

};

void Sample1_State::UpdateState(float dt) {

	_graph1->Update(dt);
	rot.y = rot.y + 0.1f;
	cam_rot.x -= AppInput::_MouseDelta.y * 0.25f;// *dt;
	cam_rot.y -= AppInput::_MouseDelta.x * 0.25f;// *dt;

	if (AppInput::_KeyState[GLFW_KEY_W])
	{
		_cam1->Move(glm::vec3(0, 0, -16.0f*dt));
	}

	if (AppInput::_KeyState[GLFW_KEY_S])
	{
		_cam1->Move(glm::vec3(0, 0, 16.0f*dt));
	}

	if (AppInput::_KeyState[GLFW_KEY_A])
	{
		_cam1->Move(glm::vec3(-16.0f*dt, 0, 0));
	}

	if (AppInput::_KeyState[GLFW_KEY_D])
	{
		_cam1->Move(glm::vec3(16.0f*dt, 0, 0));
	}

	if (AppInput::_KeyState[GLFW_KEY_SPACE]) {

		_light1->SetPosition(_cam1->GetPosition());

	}

	//	_ent1->SetPosition(glm::vec3(3, 0, 0));
	//	_ent1->Rotate(rot);

	_ui1->UpdateUI(dt);
	_cam1->Rotate(cam_rot);

}

void Sample1_State::RenderState() {

	
	_draw->SetView(SynApp::This->GetWidth(), SynApp::This->GetHeight());

	//_render->Render(_renderQueue);

	_ui1->RenderUI();
	
	return;
	auto tex = _rt1->GetTexture2D();

	
	_draw->Begin();

	_draw->DrawQuad(_ppBloom->GetTarget(2)->GetTexture2D(), glm::vec2(0, 0), glm::vec2(SynApp::This->GetWidth(),SynApp::This->GetHeight()), glm::vec4(1, 1, 1, 1));

	_draw->End();


}