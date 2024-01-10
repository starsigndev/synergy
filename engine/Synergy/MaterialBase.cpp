#include "MaterialBase.h"

#include "SynApp.h"
using namespace Diligent;
void MaterialBase::CreateVertexShader(std::string path)
{
    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood.
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
    
    SynApp::This->GetEngineFactory()->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    //m_pEngineFactory->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;

    RefCntAutoPtr<IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Material2D VS";
        ShaderCI.FilePath = path.c_str();
        SynApp::This->GetDevice()->CreateShader(ShaderCI, &pVS);
        // Create dynamic uniform buffer that will store our transformation matrix
        // Dynamic buffers can be frequently updated by the CPU
        BufferDesc CBDesc;
        CBDesc.Name = "Material2D VS Const CB";
        CBDesc.Size = sizeof(float4x4);
        CBDesc.Usage = USAGE_DYNAMIC;
        CBDesc.BindFlags = BIND_UNIFORM_BUFFER;
        CBDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
        
    }

    _vertexshader = pVS;


}

void MaterialBase::CreateFragShader(std::string path) {

    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood.
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;

    SynApp::This->GetEngineFactory()->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    //m_pEngineFactory->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;

    RefCntAutoPtr<IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Material2D  PS";
        ShaderCI.FilePath = path.c_str();
        SynApp::This->GetDevice()->CreateShader(ShaderCI, &pPS);
    }

    _fragshader = pPS;


}


RefCntAutoPtr<IPipelineState> MaterialBase::CreateGraphicsPipeline(BlendType blend, DepthFuncType depth, TexturesType textures, PRIMITIVE_TOPOLOGY prim_type, LayoutType lay_type) {

    GraphicsPipelineStateCreateInfo ps_info;
    ps_info.pVS = _vertexshader;
    ps_info.pPS = _fragshader;

    switch (depth) {
    case LessEqual:
    {
        DepthStencilStateDesc le;
        le.DepthEnable = true;
        le.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;
        ps_info.GraphicsPipeline.DepthStencilDesc = le;
    }
        break;
    case Default:
    {
        int b = 5;
    }
        break;
    case Particle:
    {
        int a = 5;
    }
        break;
    }

    RefCntAutoPtr<IPipelineState> ps;

    return ps;

}
