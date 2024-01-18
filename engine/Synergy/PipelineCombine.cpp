#include "PipelineCombine.h"
#include "Texture2D.h"

struct CombineBuf {

	glm::mat4 g_mvp;
	glm::vec4 v_Combine;
};


PipelineCombine::PipelineCombine() {

	_uniformbuffer = CreateUniform<CombineBuf>();
	CreateVertexShader("engine/pp/mat_combine.vsh");
	CreateFragShader("engine/pp/mat_combine.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

	_Combine = glm::vec2(0.5f, 0.5f);

	int b = 5;

}

void PipelineCombine::Bind(bool sp) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureAux")->Set(_auxtex->GetTexView());
	MapHelper <CombineBuf > CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_mvp = MVP;
	CBConstants->v_Combine = glm::vec4(_Combine.x,_Combine.y, 0, 0);

}