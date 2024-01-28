#include "IFileRequestor.h"
#include "ITextBox.h"
#include "IList.h"
#include "IButton.h"
#include "IWindowContent.h"
#include <iostream>
#include <filesystem>
#include "Texture2D.h"
#include <vector>
#include "SynUI.h"
namespace fs = std::filesystem;

std::vector<std::string> GetFiles(const std::string& path) {
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry)) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

std::vector<std::string> GetFolders(const std::string& path) {
    std::vector<std::string> folders;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_directory(entry)) {
            folders.push_back(entry.path().string());
        }
    }

    return folders;
}

std::string getFileNameAndExtension(const std::string& path) {
    // Use std::filesystem::path to handle the path
    std::filesystem::path filePath(path);

    // Use the filename() function to get the filename with extension
    std::string fileNameWithExtension = filePath.filename().string();

    return fileNameWithExtension;
}
std::string getLastFolder(const std::string& path) {
    // Use std::filesystem::path to handle the path
    std::filesystem::path filePath(path);

    // Use the stem() function to get the last component (folder/file) in the path
    std::string lastFolder = filePath.stem().string();

    return lastFolder;
}

IFileRequestor::IFileRequestor(std::string path) {

    RemoveSizers();
    _FileIcon = new Texture2D("edit/icon/fileIcon.png", true);
    _FolderIcon = new Texture2D("edit/icon/foldericon.png", true);

	SetSize(glm::vec2(400, 500));
	RemoveControl((IControl*)_Resizer);

	auto content = GetContent();

	auto folder = new ITextBox;

    _FolderBox = folder;

	folder->Set(glm::vec2(33, 3), glm::vec2(_Size.x - 6, 30), path);

    _Back = new IButton;

    _Back->Set(glm::vec2(3, 3), glm::vec2(29, 30),"");

    _Back->SetIcon(new Texture2D("edit/icon/exitdoor.png", true));


	auto files = new IList;

	files->Set(glm::vec2(3, 36), glm::vec2(_Size.x - 6, _Size.y - 135),"");

    auto file = new ITextBox;

    file->Set(glm::vec2(3, (42 + _Size.y - 135)), glm::vec2(_Size.x - 6, 30),"");

    auto select = new IButton;
    auto cancel = new IButton;

    select->Set(glm::vec2(3, file->GetPosition().y + 37), glm::vec2(_Size.x / 2 - 6,30), "Select File");
    cancel->Set(glm::vec2(3 + _Size.x / 2, file->GetPosition().y + 37), glm::vec2(_Size.x / 2 - 6,30), "Cancel");

    _FileList = files;
    _FileBox = file;

    BrowsePath(path);

    files->ItemSelected = [&](ListItem* item) {

        if (item == nullptr) return;

        if (item->IX == 1) {
            _FileBox->SetText(item->Text);
            _SelectedItem = item;
        }
        else if (item->IX == 0) {

            BrowsePath(item->Path);

        }

        };

   
	content->AddControl(folder);
	content->AddControl(files);
    content->AddControl(file);
    content->AddControl(select);
    content->AddControl(cancel);
    content->AddControl(_Back);

    _Back->OnClick = [&](IControl* c, void* d) {

        if (_Paths.size() > 1)
        {
            _Paths.pop_back();

            //auto np = _Paths[_Paths.size() - 1];



            BrowsePath(_Paths[_Paths.size() - 1]);
        }

        };

    select->OnClick = [&](IControl* c, void*) {

        if (FileSelected) {

            if (_SelectedItem != nullptr) {
                FileSelected(_SelectedItem->Path);
            }
            SynUI::This->SetTop(nullptr);
        }

        };

    cancel->OnClick = [](IControl* c, void* d) {

        SynUI::This->SetTop(nullptr);

        };

}

void IFileRequestor::BrowsePath(std::string path) {

    auto it = std::find(_Paths.begin(), _Paths.end(),path);

    if (it != _Paths.end()) {
    }
    else {
        _Paths.push_back(path);
    }

    _FileList->Clear();

    _FolderBox->SetText(path);

    auto folders = GetFolders(path);
    auto files1 = GetFiles(path);

    for (auto const& f : folders) {

        auto it = _FileList->AddItem(_FolderIcon, getLastFolder(f) , nullptr);
        it->Path = f;
        it->IX = 0;

    }

    for (auto const& f : files1) {

        auto it = _FileList->AddItem(_FileIcon, getFileNameAndExtension(f), nullptr);
        it->Path = f;
        it->IX = 1;


    }

}