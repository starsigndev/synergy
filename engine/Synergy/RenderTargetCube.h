#pragma once
#include "MapHelper.hpp"
#include "GraphicsUtilities.h"
#include "TextureUtilities.h"

using namespace Diligent;

class RenderTargetCube
{
public:

	RenderTargetCube(int width, int height);
	void Bind(int face);
	void Release(int face);

	int GetWidth() {
		return _Width;
	};
	int GetHeight() {
		return _Height;


	}

	RefCntAutoPtr<ITextureView> GetTexView() {
		return _TexView;
	}

private:

	int _Width, _Height;
	RefCntAutoPtr<ITexture> _Tex;
	RefCntAutoPtr<ITextureView> _TexView;
	RefCntAutoPtr<ITexture> _DepthTex;
	RefCntAutoPtr<ITextureView> _DepthTexView;
	RefCntAutoPtr<ITextureView> _FaceView[6];


};

