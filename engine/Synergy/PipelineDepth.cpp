#include "PipelineDepth.h"
#include "Material.h"
#include "Texture2D.h"
#include "Light.h"
#include "Camera.h"
struct DepthUniform {

	glm::mat4 v_MVP;
	glm::mat4 v_Proj;
	glm::mat4 v_Model;
	glm::mat4 v_View;
	glm::mat4 v_ModelInv;
	glm::vec4 v_CameraPos;
	glm::vec4 v_LightPos;
	glm::vec4 v_LightProp;
	glm::vec4 v_LightDiff;
	glm::vec4 v_LightSpec;
	glm::vec4 v_RenderProps;
	int4 v_LightMode;
	glm::vec4 v_LightDir;
	glm::vec4 v_LightCone;
	glm::vec4 v_MatDiff;
	glm::vec4 v_MatSpec;
	glm::vec4 v_CameraExt;

};

PipelineDepth::PipelineDepth() {


	_uniformbuffer = CreateUniform<DepthUniform>();
	CreateVertexShader("engine/mat_depth.vsh");
	CreateFragShader("engine/mat_depth.psh");
	_pipelinestate = CreateGP3DBasic();

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

}

void PipelineDepth::Set(Camera* camera, Node3D* node, glm::mat4 mvp) {

	//_Material = material;


	//_Light = light;
	_Camera = camera;
	_Node = node;
	MVP = mvp;

}

void PipelineDepth::Bind(bool second_pass) {

	//_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_Material->GetDiffuseMap()->GetTexView());


	//_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureSpec")->Set(_Material->GetSpecularMap()->GetTexView());
//	_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureNorm")->Set(_Material->GetNormalMap()->GetTexView());

	MapHelper<DepthUniform> CB(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CB->v_MVP = MVP;
	CB->v_Proj = glm::transpose(_Camera->GetProjectionMatrix());
	CB->v_Model = glm::transpose(_Node->GetWorldMatrix());
	CB->v_View = glm::transpose(_Camera->GetWorldMatrix());
	CB->v_ModelInv = glm::transpose(glm::inverse(_Node->GetWorldMatrix()));
	CB->v_CameraPos = glm::vec4(_Camera->GetPosition(), 1.0f);
//	CB->v_LightPos = glm::vec4(_Light->GetPosition(), 1.0f);
//	CB->v_LightProp = glm::vec4(_Light->GetRange());
//	CB->v_LightDiff = glm::vec4(_Light->GetDiffuseColor(), 1.0f);
//	CB->v_LightSpec = glm::vec4(_Light->GetSpecularColor(), 1.0f);
//	CB->v_LightMode = Diligent::int4(0, 0, 0, 0);
	CB->v_CameraExt = glm::vec4(_Camera->GetNearZ(), _Camera->GetFarZ(), 0, 0);
	CB->v_MatDiff = glm::vec4(1, 1, 1, 1);
	CB->v_MatSpec = glm::vec4(1, 1, 1, 1);


}