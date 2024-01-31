#pragma once

#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "SynApp.h"
#include "glm/glm.hpp"

using namespace Diligent;

class Texture2D;

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


class PipelineBase
{
public:

    template <typename T>
    RefCntAutoPtr<IBuffer> CreateUniform() {
        BufferDesc desc;

        desc.Name = "Uniform buffer Material Light";
        desc.Size = sizeof(T);
        desc.Usage = USAGE_DYNAMIC;
        desc.BindFlags = BIND_UNIFORM_BUFFER;
        desc.CPUAccessFlags = CPU_ACCESS_WRITE;

        RefCntAutoPtr<IBuffer> b;

        SynApp::This->GetDevice()->CreateBuffer(desc, nullptr, &b);
        return b;
    }

    void CreateVertexShader(std::string path);
    void CreateFragShader(std::string path);
    
    virtual void Bind(bool second_pass);

    void SetColorTex(Texture2D* tex);

    RefCntAutoPtr<IPipelineState> CreateGraphicsPipeline(BlendType blend, DepthFuncType depth, TexturesType textures, PRIMITIVE_TOPOLOGY prim_type, LayoutType lay_type);
    RefCntAutoPtr<IPipelineState> CreateGP2D(BlendType blend);
    RefCntAutoPtr<IPipelineState> CreateGP3DBasic();
    RefCntAutoPtr<IPipelineState> CreateGP3DLight(bool sp = false);
    RefCntAutoPtr<IPipelineState> CreateGPMeshLines();
    void SetAuxTex(Texture2D* tex) {

        _auxtex = tex;

    }

    void SetMVP(glm::mat4 mvp) {
        MVP = mvp;
    }

    glm::mat4 GetMVP() {
        return MVP;
    }

    RefCntAutoPtr<IPipelineState> GetPipelineState() {
        return _pipelinestate;
    }
    RefCntAutoPtr<IPipelineState> GetPipelineStateSP() {
        return _pipelinestateSP;
    }

   

    RefCntAutoPtr<IShaderResourceBinding> GetSRB() {
        return _srb;
    }
    RefCntAutoPtr<IShaderResourceBinding> GetSRBSP() {
        return _srbSP;
    }

protected:

    Texture2D* _colortex;
    Texture2D* _normaltex;
    Texture2D* _auxtex;

    glm::mat4 MVP;

    RefCntAutoPtr<IBuffer> _uniformbuffer;
    RefCntAutoPtr<IShader> _vertexshader;
    RefCntAutoPtr<IShader> _fragshader;
    RefCntAutoPtr<IPipelineState> _pipelinestate;
    RefCntAutoPtr<IPipelineState> _pipelinestateSP;
    RefCntAutoPtr<IShaderResourceBinding> _srb;
    RefCntAutoPtr<IShaderResourceBinding> _srbSP;
};

