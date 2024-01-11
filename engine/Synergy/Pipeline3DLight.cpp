#include "Pipeline3DLight.h"


struct LightUniform {

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
	glm::vec4 v_ClipPlane;
	int4 v_ClipMode;

};

Pipeline3DLight::Pipeline3DLight() {

}

void Pipeline3DLight::Bind(bool second_pass) {


}