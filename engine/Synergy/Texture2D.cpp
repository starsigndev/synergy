#include "Texture2D.h"
#include "SynApp.h"

Texture2D::Texture2D(std::string path) {

    TextureLoadInfo loadInfo;
    
    //Remember to deactivate.
    loadInfo.IsSRGB = false;
    loadInfo.Format = TEXTURE_FORMAT::TEX_FORMAT_RGBA8_UNORM;


    CreateTextureFromFile(path.c_str(), loadInfo, SynApp::This->GetDevice(), &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    _Width = Tex->GetDesc().Width;
    _Height = Tex->GetDesc().Height;

    }

Texture2D::Texture2D(RefCntAutoPtr<ITexture> texture, RefCntAutoPtr<ITextureView> view)
{

    Tex = texture;
    TexView = view;

}