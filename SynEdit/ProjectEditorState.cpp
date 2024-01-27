#include "ProjectEditorState.h"
#include "SynUI.h"
#include "IButton.h"
#include "SynApp.h"
#include "Texture2D.h"
#include "IWindowDock.h"
#include "IToolbar.h"
#include "IWindow.h"
#include "ILabel.h"
#include "ITextBox.h"
#include "IImage.h"
#include "IWindowContent.h"
#include "GameProject.h"
#include "IFileRequestor.h"

void ProjectEditorState::InitState() {

	auto back = new IButton;
	back->Set(glm::vec2(10, SynApp::This->GetHeight() - 115), glm::vec2(30, 30),"");
	back->SetIcon(new Texture2D("edit/icon/exitdoor.png", true));
	_UI->GetToolbar()->Add(back);


	auto project = new IWindow(true);
	project->SetPosition(glm::vec2(50, 50));
	project->SetSize(glm::vec2(512, 300));
	project->SetText("Project Editor");

	_UI->AddControl(project);
	_UI->GetDock()->DockWindow(project, AreaName::AreaCentral);   //GetDock(AreaName::AreaCentral);
	//_UI->AddControl(back);

	_UI->GetDock()->SetImage(new Texture2D("edit/bg/synergytools.png", true));
	back->OnClick = [](IControl* c, void* d)
		{
			SynApp::This->PopState();
		};


	//Project Name

	auto name_lab = new ILabel("Project Name");
	auto name_tb = new ITextBox;
	name_lab->SetPosition(glm::vec2(20, 40));
	name_tb->Set(glm::vec2(125, 35), glm::vec2(240, 30), "");

	project->GetContent()->AddControl(name_lab);
	project->GetContent()->AddControl(name_tb);

	name_tb->SetText(GameProject::Project->GetName());

	name_tb->OnChanged = [&](std::string val) {

		GameProject::Project->SetName(val);
		GameProject::Project->Save();

		};

	
	//Project Author

	auto aut_lab = new ILabel("Author(s)");
	auto aut_tb = new ITextBox;
	aut_lab->SetPosition(glm::vec2(20, 90));
	aut_tb->Set(glm::vec2(125, 85), glm::vec2(240, 30), "");

	project->GetContent()->AddControl(aut_lab);
	project->GetContent()->AddControl(aut_tb);

	aut_tb->SetText(GameProject::Project->GetAuthor());

	aut_tb->OnChanged = [&](std::string val) {

		GameProject::Project->SetAuthor(val);
		GameProject::Project->Save();

		};

	//Project Copyright

	auto copy_lab = new ILabel("Copyrights");
	auto copy_tb = new ITextBox;
	copy_lab->SetPosition(glm::vec2(20, 140));
	copy_tb->Set(glm::vec2(125, 135), glm::vec2(240, 30), "");

	project->GetContent()->AddControl(copy_lab);
	project->GetContent()->AddControl(copy_tb);

	copy_tb->SetText(GameProject::Project->GetCopyright());

	copy_tb->OnChanged = [&](std::string val) {

		GameProject::Project->SetCopyright(val);
		GameProject::Project->Save();

		};

	auto proj_img = new IImage(new Texture2D("project/general/emptyproject.png",true));
	proj_img->Set(glm::vec2(120, 250), glm::vec2(500, 400), "");
	auto b_img = new IButton;
	b_img->Set(glm::vec2(20, 620), glm::vec2(80, 30), "Browse");
	auto img_lab = new ILabel("Project Splash");
	img_lab->SetPosition(glm::vec2(20, 250));

	project->GetContent()->AddControl(proj_img);
	proj_img->SetOutline(true);
	project->GetContent()->AddControl(img_lab);
	project->GetContent()->AddControl(b_img);

	b_img->OnClick = [&](IControl* c, void* d) {

		auto req = new IFileRequestor("C:\\");
		req->SetPosition(glm::vec2(SynApp::This->GetWidth()/2-200,SynApp::This->GetHeight()/2-250));
		
		req->SetText("File Requestor");
		_UI->SetTop(req);

		};

}


void ProjectEditorState::UpdateState(float dt) {
	_UI->UpdateUI(dt);

}

void ProjectEditorState::RenderState() {

	_UI->RenderUI();
}