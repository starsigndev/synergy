#pragma once
#include "MapHelper.hpp"
#include "GraphicsUtilities.h"
#include "TextureUtilities.h"
#include "glm/glm.hpp"

using namespace Diligent;

class Texture2D;

class RenderTarget2D
{
public:

	RenderTarget2D(int width, int height);

	void Bind();
	void Release();

	int GetWidth() {
		return _Width;
	};
	int GetHeight() {
		return _Height;


	}

	void SetClearValue(glm::vec4 color);

	RefCntAutoPtr<ITextureView> GetTexView() {
		return _TexView;
	}

	Texture2D* GetTexture2D();

private:

	int _Width, _Height;
	RefCntAutoPtr<ITexture> _Tex;
	RefCntAutoPtr<ITextureView> _TexView;
	RefCntAutoPtr<ITextureView> _ShaderView;
	RefCntAutoPtr<ITexture> _DepthTex;
	RefCntAutoPtr<ITextureView> _DepthTexView; 
	glm::vec4 _ClearValue = glm::vec4(0, 0, 0, 1);

};

