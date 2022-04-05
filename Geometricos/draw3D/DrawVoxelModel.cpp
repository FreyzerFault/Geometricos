#include "DrawVoxelModel.h"

#include "DrawVoxel.h"
#include "Scene.h"


GEO::DrawVoxelModel::DrawVoxelModel(const VoxelModel& vm) : Draw(), vm(vm) {

}



void GEO::DrawVoxelModel::drawIt()
{
	// Dibujar cada uno de los voxeles del modelo
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PLAIN);
	for (const auto& voxel : vm.getVoxels())
	{
		dv.emplace_back(voxel);
		Scene::getInstance()->addModel(&dv[dv.size() - 1]);
		dv[dv.size() - 1].drawIt();
	}
}