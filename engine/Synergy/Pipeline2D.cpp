#include "Pipeline2D.h"
#include "glm/glm.hpp"
#include "Texture2D.h"
#include "SynApp.h"

struct Mat2DBuf {

	glm::mat4 g_mvp;
	glm::vec4 v_Scissor;

};

Pipeline2D::Pipeline2D() {

	_uniformbuffer = CreateUniform<Mat2DBuf>();
	CreateVertexShader("engine/mat_alphatexture.vsh");
	CreateFragShader("engine/mat_alphatexture.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb,true);

	int b = 5;

}

void Pipeline2D::Bind(bool second_pass) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
	 MapHelper<Mat2DBuf> CBConstants(SynApp::This->GetContext(),_uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	 CBConstants->g_mvp = MVP;
	 CBConstants->v_Scissor = Scissor;
	 // *CBConstants = m_WorldViewProjMatrix.Transpose();



}