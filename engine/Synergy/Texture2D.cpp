#include "Texture2D.h"
#include "SynApp.h"

Texture2D::Texture2D(std::string path) {

    TextureLoadInfo loadInfo;
    loadInfo.IsSRGB = true;

    CreateTextureFromFile("DGLogo.png", loadInfo,SynApp::This->GetDevice(), &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);


}