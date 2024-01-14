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
	Texture2D(RefCntAutoPtr<ITexture> texture, RefCntAutoPtr<ITextureView> view);
	RefCntAutoPtr<ITextureView> GetTexView() {
		return TexView;
	}

	static Texture2D* WhiteTexture() {
		return new Texture2D("res/tex/white.png");
	}
	static Texture2D* BlankNormalTexture()
	{
		return new Texture2D("res/tex/blanknormal.png");
	}
private:
	RefCntAutoPtr<ITexture> Tex;
	RefCntAutoPtr<ITextureView> TexView;
	int _Width;
	int _Height;
};

