#include "PipelineDOF.h"
#include "Texture2D.h"

struct DOFBuf {

	glm::mat4 g_mvp;
	glm::vec4 v_DOF;
};


PipelineDOF::PipelineDOF() {

	_uniformbuffer = CreateUniform<DOFBuf>();
	CreateVertexShader("engine/pp/mat_dof.vsh");
	CreateFragShader("engine/pp/mat_dof.psh");
	_pipelinestate = CreateGP2D(Blend_Alpha);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

	_DOF = glm::vec4(0.1f, 0.022f,0.001f,0);


	int b = 5;

}

void PipelineDOF::Bind(bool sp) {

	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_colortex->GetTexView());
	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureAux")->Set(_auxtex->GetTexView());
	MapHelper <DOFBuf > CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_mvp = MVP;
	CBConstants->v_DOF = glm::vec4(_DOF.x, _DOF.y,_DOF.z, 0);

}