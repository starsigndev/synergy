#include "Material2D.h"
#include "glm/glm.hpp"

struct Mat2DBuf {

	glm::mat4 g_mvp;

};

Material2D::Material2D() {

	_uniformbuffer = CreateUniform<Mat2DBuf>();
	CreateVertexShader("engine/mat_alphatexture.vsh");
	CreateFragShader("engine/mat_alphatexture.psh");
	CreateGraphicsPipeline(Blend_Alpha, LessEqual, Texs_Normal2D, PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, Layout_Normal);


}
