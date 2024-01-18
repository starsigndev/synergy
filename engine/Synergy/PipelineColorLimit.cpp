#include "PipelineColorLimit.h"
#include "Texture2D.h"

struct ColorLimitBuf {

	glm::mat4 g_mvp;
	glm::vec4 v_Combine;
};

PipelineColorLimit::PipelineColorLimit() {

	_uniformbuffer = CreateUniform<ColorLimitBuf>();
	CreateVertexShader("engine/pp/mat_colorlimit.vsh");
	CreateFragShader("engine/pp/mat_colorlimit.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

	int b = 5;

}


void PipelineColorLimit::Bind(bool second_pass) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
	MapHelper<ColorLimitBuf> CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_mvp = MVP;
	CBConstants->v_Combine = _ColorLimit;
	// *CBConstants = m_WorldViewProjMatrix.Transpose();



}

void PipelineColorLimit::SetColorLimit(glm::vec4 color) {

	_ColorLimit = color;

}