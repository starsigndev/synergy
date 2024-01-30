#include "Texture2D.h"
#include "SynApp.h"
#include <map>
#include "lodepng.h"
std::map<std::string, Texture2D*> _cache;

Texture2D::Texture2D(int size, void* pngData)
{
    std::vector<unsigned char> image;
    unsigned width, height; // Variables to store image dimensions

    // Decode the PNG image in memory
    unsigned error = lodepng::decode(image, width, height, reinterpret_cast<const unsigned char*>(pngData), size);

    TextureDesc desc;
    desc.Width = width;
    desc.Height = height;
    desc.Format = TEXTURE_FORMAT::TEX_FORMAT_RGBA8_UNORM;
    desc.Type = RESOURCE_DIM_TEX_2D;
    desc.BindFlags = BIND_SHADER_RESOURCE;


    TextureData tdata;
    tdata.NumSubresources = 1;

    TextureSubResData rdata;
    rdata.pData = image.data();
    rdata.Stride = width * 4;

    tdata.pSubResources = &rdata;
    tdata.pContext = SynApp::This->GetContext();

    SynApp::This->GetDevice()->CreateTexture(desc, &tdata, &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    _Width = width;
    _Height = height;



}

Texture2D::Texture2D(std::string path, bool srgb) {

    auto it = _cache.find(path);

    if (it != _cache.end()) {
        
        Tex = it->second->Tex;
        TexView = it->second->TexView;
        _Width = it->second->_Width;
        _Height = it->second->_Height;
        return;

        // Key found, use it
    //    std::cout << "Key " << keyToFind << " found. Value: " << it->second << std::endl;
    }
    else {

        // Key not found
        //std::cout << "Key " << keyToFind << " not found." << std::endl;
    }

    TextureLoadInfo loadInfo;

    //Remember to deactivate.
    loadInfo.IsSRGB = srgb;
    loadInfo.Format = TEXTURE_FORMAT::TEX_FORMAT_RGBA8_UNORM;

    CreateTextureFromFile(path.c_str(), loadInfo, SynApp::This->GetDevice(), &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    _Width = Tex->GetDesc().Width;
    _Height = Tex->GetDesc().Height;
    _cache[path] = this;

}

Texture2D::Texture2D(char* data, int width, int height, int channels) {

    TextureDesc desc;
    desc.Width = width;
    desc.Height = height;
    desc.Type = RESOURCE_DIM_TEX_2D;
  
        desc.Format = TEXTURE_FORMAT::TEX_FORMAT_RGBA8_UNORM;
   
    desc.BindFlags = BIND_SHADER_RESOURCE;


    TextureData tdata;
    tdata.NumSubresources = 1;
    
    TextureSubResData rdata;
    rdata.pData = data;
    rdata.Stride = width * 4;
   
    tdata.pSubResources = &rdata;
    tdata.pContext = SynApp::This->GetContext();
   
    SynApp::This->GetDevice()->CreateTexture(desc,&tdata, &Tex);
    TexView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

}

Texture2D::Texture2D(RefCntAutoPtr<ITexture> texture, RefCntAutoPtr<ITextureView> view)
{

    Tex = texture;
    TexView = view;

}

void Texture2D::Delete() {

    Tex->Release();
  //  TexView->Release();
    Tex = nullptr;
//    TexView = nullptr;


}