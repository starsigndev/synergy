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
#include "IVideo.h"
#include <iostream>
#include <filesystem>
#include "GeneralOSState.h"
#include "IMenuBar.h"
namespace fs = std::filesystem;
std::string getFileNameAndExtension2(const std::string& path) {
	// Use std::filesystem::path to handle the path
	std::filesystem::path filePath(path);

	// Use the filename() function to get the filename with extension
	std::string fileNameWithExtension = filePath.filename().string();

	return fileNameWithExtension;
}
std::string getLastFolder2(const std::string& path) {
	// Use std::filesystem::path to handle the path
	std::filesystem::path filePath(path);

	// Use the stem() function to get the last component (folder/file) in the path
	std::string lastFolder = filePath.stem().string();

	return lastFolder;
}
void ProjectEditorState::InitState() {

	auto back = new IButton;
	back->Set(glm::vec2(10, SynApp::This->GetHeight() - 115), glm::vec2(30, 30),"");
	back->SetIcon(new Texture2D("edit/icon/exitdoor.png", true));
	_UI->GetToolbar()->Add(back);

	_UI->GetMenuBar()->SetText("Synergy Tools - Project Editor");
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
			SynApp::This->PushState(new GeneralOSState);
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
	if (GameProject::Project->GetSplashImage() != "") {
		proj_img->SetImage(new Texture2D(GameProject::Project->GetSplashImage()));
	}
	_ProjImg = proj_img;

	project->GetContent()->AddControl(proj_img);
	proj_img->SetOutline(true);
	project->GetContent()->AddControl(img_lab);
	project->GetContent()->AddControl(b_img);

	b_img->OnClick = [&](IControl* c, void* d) {

		auto req = new IFileRequestor("C:\\");
		req->SetPosition(glm::vec2(SynApp::This->GetWidth()/2-200,SynApp::This->GetHeight()/2-250));
		
		req->SetText("File Requestor");
		_UI->SetTop(req);
		req->FileSelected = [&](std::string path) {

			std::cout << "File:" << path << std::endl;
				
			_ProjImg->SetImage(new Texture2D(path, true));

			GameProject::Project->SetSplashImage(path);
			GameProject::Project->Save();


			};

		};

	auto mov_lab = new ILabel("Intro Video");
	auto mov_path = new ITextBox;
	auto mov_prev = new IVideo;
	auto start_mov = new IButton;
	auto browse_mov = new IButton;
	auto end_mov = new IButton;

	project->GetContent()->AddControl(mov_lab);
	project->GetContent()->AddControl(mov_path);
	project->GetContent()->AddControl(mov_prev);
	project->GetContent()->AddControl(start_mov);
	project->GetContent()->AddControl(browse_mov);
	project->GetContent()->AddControl(end_mov);


	mov_lab->Set(glm::vec2(20, 670),glm::vec2(0,0), "Intro Movie");
	mov_path->Set(glm::vec2(20, 710),glm::vec2(180,30),"");
	mov_prev->Set(glm::vec2(240, 670), glm::vec2(400, 300), "");
	start_mov->Set(glm::vec2(700, 670), glm::vec2(80, 30), "Preview");
	end_mov->Set(glm::vec2(700, 705), glm::vec2(80, 30), "Stop");
	browse_mov->Set(glm::vec2(20, 940), glm::vec2(80, 30), "Browse");

	mov_path->SetText(getFileNameAndExtension2(GameProject::Project->GetIntroMovie()));
	_MovVid = mov_prev;

	_MovPath = mov_path;

	start_mov->OnClick = [&](IControl* c, void* d) {

		_MovVid->PlayVideo(GameProject::Project->GetIntroMovie());

		};

	end_mov->OnClick = [&](IControl* c, void* d) {

		_MovVid->Stop();

		};

	browse_mov->OnClick = [&](IControl* c, void* d) {

		auto req = new IFileRequestor("C:\\");
		req->SetPosition(glm::vec2(SynApp::This->GetWidth() / 2 - 200, SynApp::This->GetHeight() / 2 - 250));

		req->SetText("Select Intro Movie");
		_UI->SetTop(req);
		req->FileSelected = [&](std::string path) {

			std::cout << "File:" << path << std::endl;

			//_ProjImg->SetImage(new Texture2D(path, true));
			
			_MovPath->SetText(getFileNameAndExtension2(path));

			GameProject::Project->SetIntroMovie(path);
			GameProject::Project->Save();


			};


		};


}


void ProjectEditorState::UpdateState(float dt) {
	_UI->UpdateUI(dt);

}

void ProjectEditorState::RenderState() {

	_UI->RenderUI();
}