#include "Pipeline3DBasic.h"
#include "Material.h"
#include "Texture2D.h"

struct Basic3DUniform {

    glm::mat4 g_MVP;

};

Pipeline3DBasic::Pipeline3DBasic() {

	_uniformbuffer = CreateUniform<Basic3DUniform>();
	CreateVertexShader("engine/mat_basic.vsh");
	CreateFragShader("engine/mat_basic.psh");
	_pipelinestate = CreateGP3DBasic();

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

}

void Pipeline3DBasic::Set(Material* material,glm::mat4 mvp) {

	_Material = material;
	MVP = mvp;

}

void Pipeline3DBasic::Bind(bool second_pass) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_Material->GetDiffuseMap()->GetTexView());
	MapHelper<Basic3DUniform> CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_MVP = MVP;

}