#include "PipelineBlur.h"

#include "Texture2D.h"

struct BlurBuf {

	glm::mat4 g_mvp;
	glm::vec4 v_Combine;
};

PipelineBlur::PipelineBlur() {

	_uniformbuffer = CreateUniform<BlurBuf>();
	CreateVertexShader("engine/pp/mat_blur.vsh");
	CreateFragShader("engine/pp/mat_blur.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

	int b = 5;

}


void PipelineBlur::Bind(bool second_pass) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
	MapHelper <BlurBuf > CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_mvp = MVP;
	CBConstants->v_Combine = glm::vec4(_Blur, 0, 0, 0);
	// *CBConstants = m_WorldViewProjMatrix.Transpose();



}