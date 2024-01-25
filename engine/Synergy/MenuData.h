#pragma once

struct  MenuItem {

    MenuItem(std::string text, void* data = nullptr) {
        Text = text;
        Data = data;

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

};

struct ListItem {

    std::string Text;
    void* Data;

};