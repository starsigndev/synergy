#include "IFileRequestor.h"
#include "ITextBox.h"
#include "IList.h"
#include "IButton.h"
#include "IWindowContent.h"
#include <iostream>
#include <filesystem>
#include <vector>
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


IFileRequestor::IFileRequestor(std::string path) {

	SetSize(glm::vec2(400, 500));
	RemoveControl((IControl*)_Resizer);

	auto content = GetContent();

	auto folder = new ITextBox;

	folder->Set(glm::vec2(3, 3), glm::vec2(_Size.x - 6, 30), path);

	auto files = new IList;

	files->Set(glm::vec2(3, 36), glm::vec2(_Size.x - 6, _Size.y - 135),"");

    auto folders = GetFolders(path);
    auto files1 = GetFiles(path);

    for (auto const& f : folders) {

        files->AddItem(f, nullptr);

    }

    for (auto const& f : files1) {

        files->AddItem(f, nullptr);

    }


	content->AddControl(folder);
	content->AddControl(files);


}