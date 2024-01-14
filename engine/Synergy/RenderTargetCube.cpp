#include "RenderTargetCube.h"
#include "SynApp.h"

RenderTargetCube::RenderTargetCube(int width, int height) {

	_Width = width;
	_Height = height;
	
	TextureDesc desc;
	desc.Name = "RenderTarget Cube";
	desc.Width = (Uint32)width;
	desc.Height = (Uint32)height;
	desc.Type = RESOURCE_DIMENSION::RESOURCE_DIM_TEX_CUBE;
	desc.MipLevels = 1;
	desc.ArraySize = 6;
	desc.Usage = USAGE_DEFAULT;
	desc.Format = TEXTURE_FORMAT::TEX_FORMAT_RGBA32_FLOAT;
	desc.BindFlags = BIND_SHADER_RESOURCE | BIND_RENDER_TARGET;
	desc.ClearValue.Format = desc.Format;
	desc.ClearValue.Color[0] = 0;
	desc.ClearValue.Color[1] = 0;
	desc.ClearValue.Color[2] = 0;
	desc.ClearValue.Color[3] = 0;
	SynApp::This->GetDevice()->CreateTexture(desc, nullptr, &_Tex);

	_TexView = _Tex->GetDefaultView(TEXTURE_VIEW_TYPE::TEXTURE_VIEW_SHADER_RESOURCE);
	for (int i = 0; i < 6; i++) {
		TextureViewDesc vdesc;
		vdesc.Name = "TexCube Face";
		vdesc.TextureDim = RESOURCE_DIMENSION::RESOURCE_DIM_TEX_2D_ARRAY;
		vdesc.ViewType = TEXTURE_VIEW_TYPE::TEXTURE_VIEW_RENDER_TARGET;
		vdesc.MostDetailedMip = 0;
		vdesc.FirstArraySlice = i;
		vdesc.NumArraySlices = 1;
		_Tex->CreateView(vdesc,&_FaceView[i]);

	}

	TextureDesc ddesc;
	ddesc.Name = "RenderCube Depth";
	ddesc.Format = TEXTURE_FORMAT::TEX_FORMAT_D32_FLOAT;
	ddesc.BindFlags = BIND_DEPTH_STENCIL;
	ddesc.ClearValue.Format = ddesc.Format;
	ddesc.ClearValue.DepthStencil.Depth = 1.0f;
	ddesc.ClearValue.DepthStencil.Stencil = 0;
	ddesc.Type = RESOURCE_DIMENSION::RESOURCE_DIM_TEX_2D;
	ddesc.Width = (Uint32)width;
	ddesc.Height = (Uint32)height;
	SynApp::This->GetDevice()->CreateTexture(ddesc, nullptr, &_DepthTex);
	_DepthTexView = _DepthTex->GetDefaultView(TEXTURE_VIEW_TYPE::TEXTURE_VIEW_DEPTH_STENCIL);
	
	int b = 5;



}


void RenderTargetCube::Bind(int face) {

	SynApp::This->SetBoundCubeRT(this);

	float* col = new float[4];
	col[0] = 1;
	col[1] = 1;
	col[2] = 1;
	col[3] = 0;

	SynApp::This->GetContext()->SetRenderTargets(1, &_FaceView[face], _DepthTexView, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	SynApp::This->GetContext()->ClearRenderTarget(_FaceView[face], col, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	SynApp::This->GetContext()->ClearDepthStencil(_DepthTexView, CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

}

void RenderTargetCube::Release(int face) {

	SynApp::This->SetBoundCubeRT(nullptr);
	auto rt = SynApp::This->GetSwapChain()->GetCurrentBackBufferRTV();

	SynApp::This->GetContext()->SetRenderTargets(1, &rt, SynApp::This->GetSwapChain()->GetDepthBufferDSV(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

}