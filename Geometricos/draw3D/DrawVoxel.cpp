#include "DrawVoxel.h"
#include "AABB.h"

GEO::DrawVoxel::DrawVoxel(const Voxel& voxel) : DrawAABB(static_cast<AABB>(voxel)), voxel(voxel) {
}


void GEO::DrawVoxel::drawIt() {
	colorAct = voxel.getColor();
	DrawAABB::drawIt();
}
