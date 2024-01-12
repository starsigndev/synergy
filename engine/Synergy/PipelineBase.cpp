#include "PipelineBase.h"
#include "Texture2D.h"
#include "SynApp.h"
#include "MapHelper.hpp"
using namespace Diligent;
void PipelineBase::CreateVertexShader(std::string path)
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

void PipelineBase::CreateFragShader(std::string path) {

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

RefCntAutoPtr<IPipelineState> PipelineBase::CreateGP3DLight() {

    GraphicsPipelineStateCreateInfo ps_info;
    ps_info.pVS = _vertexshader;
    ps_info.pPS = _fragshader;
    ps_info.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    ps_info.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_BACK;



    DepthStencilStateDesc le;
    le.DepthEnable = true;
    le.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;

    ps_info.GraphicsPipeline.DepthStencilDesc = le;


    ps_info.GraphicsPipeline.SmplDesc.Count = 1;
    ps_info.GraphicsPipeline.NumRenderTargets = 1;

    ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = false;
    ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_ONE;
    ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_ZERO;


    ps_info.GraphicsPipeline.RTVFormats[0] = SynApp::This->GetSwapChain()->GetDesc().ColorBufferFormat;
    ps_info.GraphicsPipeline.DSVFormat = SynApp::This->GetSwapChain()->GetDesc().DepthBufferFormat;

    std::vector<LayoutElement> LayoutElems = {
LayoutElement{0, 0, 3, VT_FLOAT32, False},
// Attribute 1 - vertex color
LayoutElement{1, 0, 4, VT_FLOAT32, False},

   LayoutElement{2, 0, 3, VT_FLOAT32, False},
LayoutElement{3, 0, 3, VT_FLOAT32, False},
LayoutElement{4, 0, 3, VT_FLOAT32, False},
   LayoutElement{5, 0, 3, VT_FLOAT32, False},
      LayoutElement{6, 0, 4, VT_FLOAT32, False},
         LayoutElement{7, 0, 4, VT_FLOAT32, False},
    };

    ps_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems.data();
    ps_info.GraphicsPipeline.InputLayout.NumElements = LayoutElems.size();


    std::vector<ShaderResourceVariableDesc> Vars = {


        {SHADER_TYPE_PIXEL, "v_Texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
                {SHADER_TYPE_PIXEL, "v_TextureNorm", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
                        {SHADER_TYPE_PIXEL, "v_TextureSpec", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
                                {SHADER_TYPE_PIXEL, "v_Shadow", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},



    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.Variables = Vars.data();
    ps_info.PSODesc.ResourceLayout.NumVariables = Vars.size();

    SamplerDesc SamLinearClampDesc
    {
        FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
       TEXTURE_ADDRESS_WRAP, TEXTURE_ADDRESS_WRAP, TEXTURE_ADDRESS_CLAMP
    };


    std::vector<ImmutableSamplerDesc> ImtblSamplers =
    {
        {SHADER_TYPE_PIXEL, "v_Texture", SamLinearClampDesc},
           {SHADER_TYPE_PIXEL, "v_TextureNorm", SamLinearClampDesc},
              {SHADER_TYPE_PIXEL, "v_TextureSpec", SamLinearClampDesc},
                 {SHADER_TYPE_PIXEL, "v_Shadow", SamLinearClampDesc},
    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.ImmutableSamplers = ImtblSamplers.data();
    ps_info.PSODesc.ResourceLayout.NumImmutableSamplers = ImtblSamplers.size();

    RefCntAutoPtr<IPipelineState> ps;
    SynApp::This->GetDevice()->CreatePipelineState(ps_info, &ps);
    return ps;


}

RefCntAutoPtr<IPipelineState> PipelineBase::CreateGP3DBasic() {

    GraphicsPipelineStateCreateInfo ps_info;
    ps_info.pVS = _vertexshader;
    ps_info.pPS = _fragshader;
    ps_info.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    ps_info.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_BACK;



    DepthStencilStateDesc le;
    le.DepthEnable = true;
    le.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;
    
    ps_info.GraphicsPipeline.DepthStencilDesc = le;


    ps_info.GraphicsPipeline.SmplDesc.Count = 1;
    ps_info.GraphicsPipeline.NumRenderTargets = 1;

        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = false;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_ONE;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_ZERO;
  

    ps_info.GraphicsPipeline.RTVFormats[0] = SynApp::This->GetSwapChain()->GetDesc().ColorBufferFormat;
    ps_info.GraphicsPipeline.DSVFormat = SynApp::This->GetSwapChain()->GetDesc().DepthBufferFormat;

    std::vector<LayoutElement> LayoutElems = {
LayoutElement{0, 0, 3, VT_FLOAT32, False},
// Attribute 1 - vertex color
LayoutElement{1, 0, 4, VT_FLOAT32, False},

   LayoutElement{2, 0, 3, VT_FLOAT32, False},
LayoutElement{3, 0, 3, VT_FLOAT32, False},
LayoutElement{4, 0, 3, VT_FLOAT32, False},
   LayoutElement{5, 0, 3, VT_FLOAT32, False},
      LayoutElement{6, 0, 4, VT_FLOAT32, False},
         LayoutElement{7, 0, 4, VT_FLOAT32, False},
    };

    ps_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems.data();
    ps_info.GraphicsPipeline.InputLayout.NumElements = LayoutElems.size();


    std::vector<ShaderResourceVariableDesc> Vars = {


        {SHADER_TYPE_PIXEL, "v_Texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},


    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.Variables = Vars.data();
    ps_info.PSODesc.ResourceLayout.NumVariables = Vars.size();

    SamplerDesc SamLinearClampDesc
    {
        FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
        TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP
    };


    std::vector<ImmutableSamplerDesc> ImtblSamplers =
    {
        {SHADER_TYPE_PIXEL, "v_Texture", SamLinearClampDesc},
 

    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.ImmutableSamplers = ImtblSamplers.data();
    ps_info.PSODesc.ResourceLayout.NumImmutableSamplers = ImtblSamplers.size();

    RefCntAutoPtr<IPipelineState> ps;
    SynApp::This->GetDevice()->CreatePipelineState(ps_info, &ps);
    return ps;

}

RefCntAutoPtr<IPipelineState> PipelineBase::CreateGP2D(BlendType blend) {


    GraphicsPipelineStateCreateInfo ps_info;
    ps_info.pVS = _vertexshader;
    ps_info.pPS = _fragshader;
    ps_info.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    ps_info.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;



        DepthStencilStateDesc le;
        le.DepthEnable = true;
        le.DepthFunc = COMPARISON_FUNC_LESS_EQUAL;
        ps_info.GraphicsPipeline.DepthStencilDesc = le;
 

    ps_info.GraphicsPipeline.SmplDesc.Count = 1;
    ps_info.GraphicsPipeline.NumRenderTargets = 1;

    switch (blend) {
    case Blend_None:
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = false;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_ONE;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_ZERO;
        break;
    case Blend_Alpha:
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = true;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_SRC_ALPHA;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_INV_SRC_ALPHA;
        break;
    case Blend_Additive:
        break;

    }

    ps_info.GraphicsPipeline.RTVFormats[0] = SynApp::This->GetSwapChain()->GetDesc().ColorBufferFormat;
   
    std::vector<LayoutElement> LayoutElems = {
LayoutElement{0, 0, 3, VT_FLOAT32, False},
// Attribute 1 - vertex color
LayoutElement{1, 0, 4, VT_FLOAT32, False},

   LayoutElement{2, 0, 3, VT_FLOAT32, False},
LayoutElement{3, 0, 3, VT_FLOAT32, False},
LayoutElement{4, 0, 3, VT_FLOAT32, False},
   LayoutElement{5, 0, 3, VT_FLOAT32, False},
      LayoutElement{6, 0, 4, VT_FLOAT32, False},
         LayoutElement{7, 0, 4, VT_FLOAT32, False},
    };

    ps_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems.data();
    ps_info.GraphicsPipeline.InputLayout.NumElements = LayoutElems.size();


    std::vector<ShaderResourceVariableDesc> Vars = {


        {SHADER_TYPE_PIXEL, "v_Texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
        {SHADER_TYPE_PIXEL, "v_TextureAux", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}

    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.Variables = Vars.data();
    ps_info.PSODesc.ResourceLayout.NumVariables = Vars.size();

    SamplerDesc SamLinearClampDesc
    {
        FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
        TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP
    };


    std::vector<ImmutableSamplerDesc> ImtblSamplers =
    {
        {SHADER_TYPE_PIXEL, "v_Texture", SamLinearClampDesc},
         {SHADER_TYPE_PIXEL, "v_TextureAux", SamLinearClampDesc}

    };
    // clang-format on
    ps_info.PSODesc.ResourceLayout.ImmutableSamplers = ImtblSamplers.data();
    ps_info.PSODesc.ResourceLayout.NumImmutableSamplers = ImtblSamplers.size();

    RefCntAutoPtr<IPipelineState> ps;
    SynApp::This->GetDevice()->CreatePipelineState(ps_info, &ps);
    return ps;
}


RefCntAutoPtr<IPipelineState> PipelineBase::CreateGraphicsPipeline(BlendType blend, DepthFuncType depth, TexturesType textures, PRIMITIVE_TOPOLOGY prim_type, LayoutType lay_type) {

    GraphicsPipelineStateCreateInfo ps_info;
    ps_info.pVS = _vertexshader;
    ps_info.pPS = _fragshader;
    ps_info.GraphicsPipeline.PrimitiveTopology = prim_type;
    ps_info.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;


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

    ps_info.GraphicsPipeline.SmplDesc.Count = 1;
    ps_info.GraphicsPipeline.NumRenderTargets = 1;

    switch (blend) {
    case Blend_None:
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = false;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_ONE;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_ZERO;
        break;
    case Blend_Alpha:
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = true;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = BLEND_FACTOR_SRC_ALPHA;
        ps_info.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = BLEND_FACTOR_INV_SRC_ALPHA;
        break;
    case Blend_Additive:
        break;

    }

    ps_info.GraphicsPipeline.RTVFormats[0] = SynApp::This->GetSwapChain()->GetDesc().ColorBufferFormat;
    //ps_info.GraphicsPipeline.DSVFormat = SynApp::This->GetSwapChain()->GetDesc().DepthBufferFormat;

   // switch (lay_type) {
  //  case Layout_Normal:

       
        /*
        LayoutElement LayoutElems[] =
        {
            // Attribute 0 - vertex position
            LayoutElement{0, 0, 3, VT_FLOAT32, False},
            // Attribute 1 - vertex color
            LayoutElement{1, 0, 4, VT_FLOAT32, False},

               LayoutElement{2, 0, 3, VT_FLOAT32, False},
           LayoutElement{3, 0, 3, VT_FLOAT32, False},
           LayoutElement{4, 0, 3, VT_FLOAT32, False},
              LayoutElement{5, 0, 3, VT_FLOAT32, False},
                 LayoutElement{6, 0, 4, VT_FLOAT32, False},
                    LayoutElement{7, 0, 4, VT_FLOAT32, False},
        };
       */
        

        
        for (int i = 0;i < 8;i++) {
         //   LayoutElems[i].BufferSlot = 0;
        }
        //LayoutElems[0].BufferSlot = 0;
        std::vector<LayoutElement> LayoutElems = {
 LayoutElement{0, 0, 3, VT_FLOAT32, False},
 // Attribute 1 - vertex color
 LayoutElement{1, 0, 4, VT_FLOAT32, False},

    LayoutElement{2, 0, 3, VT_FLOAT32, False},
LayoutElement{3, 0, 3, VT_FLOAT32, False},
LayoutElement{4, 0, 3, VT_FLOAT32, False},
   LayoutElement{5, 0, 3, VT_FLOAT32, False},
      LayoutElement{6, 0, 4, VT_FLOAT32, False},
         LayoutElement{7, 0, 4, VT_FLOAT32, False},
        };
        
        ps_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems.data();
        ps_info.GraphicsPipeline.InputLayout.NumElements = LayoutElems.size();
        


       // ps_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems;
       // ps_info.GraphicsPipeline.InputLayout.NumElements = co

     //   break;
   // }

    //switch (textures) {
   // case Texs_Normal2D:

        std::vector<ShaderResourceVariableDesc> Vars = {
        
        
            {SHADER_TYPE_PIXEL, "v_Texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE},
            {SHADER_TYPE_PIXEL, "v_TextureAux", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
        
        };
        // clang-format on
        ps_info.PSODesc.ResourceLayout.Variables = Vars.data();
        ps_info.PSODesc.ResourceLayout.NumVariables = Vars.size();

        SamplerDesc SamLinearClampDesc
        {
            FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
            TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP
        };


        std::vector<ImmutableSamplerDesc> ImtblSamplers =
        {
            {SHADER_TYPE_PIXEL, "v_Texture", SamLinearClampDesc},
             {SHADER_TYPE_PIXEL, "v_TextureAux", SamLinearClampDesc}
        
        };
        // clang-format on
        ps_info.PSODesc.ResourceLayout.ImmutableSamplers = ImtblSamplers.data();
        ps_info.PSODesc.ResourceLayout.NumImmutableSamplers = ImtblSamplers.size();
       

      //  break;
    //}




    RefCntAutoPtr<IPipelineState> ps;
    SynApp::This->GetDevice()->CreatePipelineState(ps_info, &ps);

    return ps;

}

void PipelineBase::SetColorTex(Texture2D* tex) {
    _colortex = tex;
}

void PipelineBase::Bind(bool second_pass) {

    _srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
   // MapHelper<float4x4> CBConstants(m_pImmediateContext, m_VSConstants, MAP_WRITE, MAP_FLAG_DISCARD);
   // *CBConstants = m_WorldViewProjMatrix.Transpose();
}