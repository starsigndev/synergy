#pragma once

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "SynApp.h"

using namespace Diligent;

enum BlendType {
    Blend_None,Blend_Additive,Blend_Alpha,Blend_Terrain
};


enum DepthFuncType {
    LessEqual,Default,Particle
};

enum TexturesType {

    Texs_Standard,Texs_None,Texs_Normal2D,Texs_Terrain,Texs_Water

};

enum LayoutType {
    Layout_Normal,Layout_Terrain,Layout_Water
};


class MaterialBase
{
public:

    template <typename T>
    RefCntAutoPtr<IBuffer> CreateUniform() {
        BufferDesc desc;

        desc.Name = "Uniform buffer Material Light";
        desc.Size = sizeof(T);
        desc.Usage = USAGE_DEFAULT;
        desc.BindFlags = BIND_UNIFORM_BUFFER;
        //desc.CPUAccessFlags = CPUAccessFlags::Write;

        RefCntAutoPtr<IBuffer> b;

        SynApp::This->GetDevice()->CreateBuffer(desc, nullptr, &b);
        return b;
    }

    void CreateVertexShader(std::string path);
    void CreateFragShader(std::string path);
    RefCntAutoPtr<IPipelineState> CreateGraphicsPipeline(BlendType blend, DepthFuncType depth, TexturesType textures, PRIMITIVE_TOPOLOGY prim_type, LayoutType lay_type);

protected:

    RefCntAutoPtr<IBuffer> _uniformbuffer;
    RefCntAutoPtr<IShader> _vertexshader;
    RefCntAutoPtr<IShader> _fragshader;

};

