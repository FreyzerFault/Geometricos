#include "DrawVoxel.h"
#include "AABB.h"

GEO::DrawVoxel::DrawVoxel(const Voxel& voxel) : DrawAABB(static_cast<AABB>(voxel)), voxel(voxel) {
}


void GEO::DrawVoxel::drawIt() {

	setShaderProgram("algeom");
	setDrawMode(TypeDraw::WIREFRAME);
	if (voxel.getType() != TypeVoxel::NP)
		colorAct = voxel.getColor();
	Scene::getInstance()->addModel(this);
}

void GEO::DrawVoxel::drawIt(TypeColor color)
{
	setColorActivo(color);
	drawIt();
}
