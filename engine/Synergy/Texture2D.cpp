#include "Texture2D.h"
#include "SynApp.h"

Texture2D::Texture2D(std::string path) {

    TextureLoadInfo loadInfo;
    
    //Remember to deactivate.
    loadInfo.IsSRGB = true;


    CreateTextureFromFile(path.c_str(), loadInfo, SynApp::This->GetDevice(), &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

    }