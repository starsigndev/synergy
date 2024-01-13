#include "Pipeline3DActorLight.h"
#include "Material.h"
#include "Texture2D.h"
#include "Light.h"
#include "Camera.h"

struct ActorLightUniform {

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
	glm::mat4 v_Bones[100];
	//glm::vec4 v_ClipPlane;
	//int4 v_ClipMode;


};

Pipeline3DActorLight::Pipeline3DActorLight() {

	_uniformbuffer = CreateUniform<ActorLightUniform>();
	CreateVertexShader("engine/mesh_actorlit.vsh");
	CreateFragShader("engine/mesh_actorlit.psh");
	_pipelinestate = CreateGP3DLight();
	_pipelinestateSP = CreateGP3DLight(true);

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);
	_pipelinestateSP->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestateSP->CreateShaderResourceBinding(&_srbSP, true);

}

void Pipeline3DActorLight::Set(Material* material, Light* light, Camera* camera, Node3D* node, glm::mat4 mvp,const glm::mat4* bones) {

	_Material = material;
	_Light = light;
	_Camera = camera;
	_Node = node;
	MVP = mvp;
	for (int i = 0; i < 100; i++)
	{
		_BoneMatrices[i] = bones[i];
	}
	//_BoneMatrices = bones;

}

void Pipeline3DActorLight::Bind(bool second_pass) {

	if (second_pass) {
		_srbSP->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_Material->GetDiffuseMap()->GetTexView(),SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
		_srbSP->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureSpec")->Set(_Material->GetSpecularMap()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
		_srbSP->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureNorm")->Set(_Material->GetNormalMap()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
	//	_srbSP->GetVariableByName(SHADER_TYPE_PIXEL, "v_Shadow")->Set(_Light->GetShadowRT()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
	}
	else {
		_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Texture")->Set(_Material->GetDiffuseMap()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
		_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureSpec")->Set(_Material->GetSpecularMap()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
		_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_TextureNorm")->Set(_Material->GetNormalMap()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
		//_srb->GetVariableByName(SHADER_TYPE_PIXEL, "v_Shadow")->Set(_Light->GetShadowRT()->GetTexView(), SET_SHADER_RESOURCE_FLAG_ALLOW_OVERWRITE);
	}
	MapHelper<ActorLightUniform> CB(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CB->v_MVP = MVP;
	CB->v_Proj = glm::transpose(_Camera->GetProjectionMatrix());
	CB->v_Model = glm::transpose(_Node->GetWorldMatrix());
	CB->v_View = glm::transpose(_Camera->GetWorldMatrix());
	CB->v_ModelInv = glm::transpose(glm::inverse(_Node->GetWorldMatrix()));
	CB->v_CameraPos = glm::vec4(_Camera->GetPosition(), 1.0f);
	CB->v_LightPos = glm::vec4(_Light->GetPosition(), 1.0f);
	CB->v_LightProp = glm::vec4(_Light->GetRange(), 0, 0, 0);
	CB->v_LightDiff = glm::vec4(_Light->GetDiffuseColor(), 1.0f);
	CB->v_LightSpec = glm::vec4(_Light->GetSpecularColor(), 1.0f);
	CB->v_LightMode = Diligent::int4(0, 0, 0, 0);
	CB->v_CameraExt = glm::vec4(_Camera->GetNearZ(), _Camera->GetFarZ(), 0, 0);
	CB->v_MatDiff = glm::vec4(1, 1, 1, 1);
	CB->v_MatSpec = glm::vec4(1, 1, 1, 1);
	
	for (int i = 0; i < 100; i++) {
		CB->v_Bones[i] = glm::transpose(_BoneMatrices[i]);
//		CB->v_Bones[i] = glm::transpose(glm::mat4(1.0f));
	}
	//CB->v_Bones = _BoneMatrices;

	//CB->v_RenderProps = glm::vec4();


	//consts.v_LightProp = new Vector4(Vivid.Renderer.SceneRenderer.CurrentLight.Range, 0, 0, 0);



}