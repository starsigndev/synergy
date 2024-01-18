#include "RenderTarget2D.h"
#include "SynApp.h"
#include "Texture2D.h"

RenderTarget2D::RenderTarget2D(int width, int height) {

	_Width = width;
	_Height = height;

	TextureDesc desc;
	desc.Name = "RenderTarget2D texture";
	desc.Type = RESOURCE_DIM_TEX_2D;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.Format = TEX_FORMAT_RGBA8_UNORM;
	desc.BindFlags = BIND_RENDER_TARGET | BIND_SHADER_RESOURCE;
	desc.ClearValue.Format = desc.Format;
	desc.ClearValue.Color[0] = 0;
	desc.ClearValue.Color[1] = 0;
	desc.ClearValue.Color[2] = 0;
	desc.ClearValue.Color[3] = 1;
	SynApp::This->GetDevice()->CreateTexture(desc, nullptr, &_Tex);

	_TexView = _Tex->GetDefaultView(TEXTURE_VIEW_RENDER_TARGET);
	_ShaderView = _Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

	TextureDesc ddesc = desc;
	ddesc.Name = "RenderTarget2D depth";
	ddesc.Format = TEX_FORMAT_D24_UNORM_S8_UINT;
	ddesc.BindFlags = BIND_DEPTH_STENCIL;
	ddesc.ClearValue.Format = ddesc.Format;
	ddesc.ClearValue.DepthStencil.Depth = 1.0f;
	ddesc.ClearValue.DepthStencil.Stencil = 0;
	SynApp::This->GetDevice()->CreateTexture(ddesc, nullptr, &_DepthTex);
	_DepthTexView = _DepthTex->GetDefaultView(TEXTURE_VIEW_DEPTH_STENCIL);




}

void RenderTarget2D::Bind() {

	SynApp::This->SetBound2DRT(this);

	float* col = new float[4];
	col[0] = 0;
	col[1] = 0;
	col[2] = 0;
	col[3] = 0;

	SynApp::This->GetContext()->SetRenderTargets(1,&_TexView, _DepthTexView, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	SynApp::This->GetContext()->ClearRenderTarget(_TexView, col, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	SynApp::This->GetContext()->ClearDepthStencil(_DepthTexView, CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

}

void RenderTarget2D::Release() {

	SynApp::This->SetBound2DRT(nullptr);
	auto rt = SynApp::This->GetSwapChain()->GetCurrentBackBufferRTV();

	SynApp::This->GetContext()->SetRenderTargets(1, &rt, SynApp::This->GetSwapChain()->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


}

void RenderTarget2D::SetClearValue(glm::vec4 color) {

	_ClearValue = color;

}

Texture2D* RenderTarget2D::GetTexture2D() {

	return new Texture2D(_Tex, _ShaderView);

}