#pragma once
#include <string>
#include <vector>

class Texture2D;

struct  MenuItem {

    MenuItem(std::string text, void* data = nullptr) {
        Text = text;
        Data = data;

    }
    void AddSeperator() {
        MenuItem* sep = new MenuItem("", nullptr);
        sep->Seperator = true;
        Items.push_back(sep);
    }
    MenuItem* AddItem(std::string text, void* data = nullptr) {
        MenuItem* item = new MenuItem(text, data);
        Items.push_back(item);
        return item;
    }
    void SetIcon(Texture2D* icon) {
        Icon = icon;
    }
    std::string Text;
    void* Data;
    std::vector<MenuItem*> Items;
    bool Open = false;
    int DrawX, DrawY;
    Texture2D* Icon = nullptr;
    std::function<void()> OnClick;
    bool Seperator = false;
};

struct ListItem {

    std::string Text;
    void* Data;
    Texture2D* Icon = nullptr;
    int IX = 0;
    int IY = 0;
    std::string Path;

};