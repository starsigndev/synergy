#pragma once

#include "TextureBase.h"
#include <string>
#include "MapHelper.hpp"
#include "GraphicsUtilities.h"
#include "TextureUtilities.h"


using namespace Diligent;

class Texture2D : public TextureBase
{
public:
	Texture2D(std::string path);
private:
	RefCntAutoPtr<ITexture> Tex;
	RefCntAutoPtr<ITextureView> TexView;
};

