#include "Material2D.h"
#include "glm/glm.hpp"
#include "Texture2D.h"
#include "SynApp.h"

struct Mat2DBuf {

	glm::mat4 g_mvp;

};

Material2D::Material2D() {

	_uniformbuffer = CreateUniform<Mat2DBuf>();
	CreateVertexShader("engine/mat_alphatexture.vsh");
	CreateFragShader("engine/mat_alphatexture.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb,true);

	int b = 5;

}

void Material2D::Bind(bool second_pass) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
	 MapHelper<Mat2DBuf> CBConstants(SynApp::This->GetContext(),_uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	 CBConstants->g_mvp = MVP;
	 // *CBConstants = m_WorldViewProjMatrix.Transpose();



}