#include "DrawVoxel.h"
#include "AABB.h"

GEO::DrawVoxel::DrawVoxel(const Voxel& voxel) : DrawAABB(static_cast<AABB>(voxel)), voxel(voxel) {
}


void GEO::DrawVoxel::drawIt() {

	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PLAIN);
	colorAct = voxel.getColor();
	Scene::getInstance()->addModel(this);
}
