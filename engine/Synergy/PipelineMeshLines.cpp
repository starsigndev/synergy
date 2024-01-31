#include "PipelineMeshLines.h"

struct MeshLinesUniform {

    glm::mat4 g_MVP;

};

PipelineMeshLines::PipelineMeshLines() {

	_uniformbuffer = CreateUniform<MeshLinesUniform>();
	CreateVertexShader("engine/mesh_lines.vsh");
	CreateFragShader("engine/mesh_lines.psh");
	
	_pipelinestate = CreateGPMeshLines();

	_pipelinestate->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(_uniformbuffer);

	_pipelinestate->CreateShaderResourceBinding(&_srb, true);

}

void PipelineMeshLines::Set(glm::mat4 mvp) {


	//_Material = material;
	MVP = mvp;

}

void PipelineMeshLines::Bind(bool second_pass) {


	MapHelper<MeshLinesUniform> CBConstants(SynApp::This->GetContext(), _uniformbuffer, MAP_WRITE, MAP_FLAG_DISCARD);
	CBConstants->g_MVP = MVP;

}