#include "GameProject.h"
#include "VFile.h"

GameProject* GameProject::Project = nullptr;
std::string GameProject::_ProjectPath = "c:\\synergy\\synedit\\";

GameProject::GameProject() {

	if (Project != nullptr) {
		return;
	}

	if (VFile::Exists("project/general/project.info")) {
		Load();
	}
	else {
		Save();
	}

	Project = this;

}

void GameProject::Save() {

	VFile* file = new VFile("project/general/project.info", FileMode::Write);

	file->WriteString(_Name.c_str());
	file->WriteString(_Author.c_str());
	file->WriteString(_Copyright.c_str());
	file->WriteString(_SplashImagePath.c_str());
	file->WriteString(_IntroMoviePath.c_str());

	file->Close();

}

void GameProject::Load() {

	VFile* file = new VFile("project/general/project.info", FileMode::Read);

	_Name = file->ReadString();
	_Author = file->ReadString();
	_Copyright = file->ReadString();
	_SplashImagePath = file->ReadString();
	_IntroMoviePath = file->ReadString();

	file->Close();

}