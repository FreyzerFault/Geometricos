#include "DrawVoxelModel.h"


GEO::DrawVoxelModel::DrawVoxelModel(VoxelModel vm) : Draw(), vm(std::move(vm)) {

}



void GEO::DrawVoxelModel::drawIt(TypeVoxel type)
{
	// Dibujar cada uno de los voxeles del modelo
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PLAIN);
		
	const Vec3D gridSize = vm.getGridSize();

	// Reservamos espacio para la Malla 3D:
	dv = new DrawVoxel***[gridSize.getX()];

	for (int x = 0; x < gridSize.getX(); ++x)
	{
		dv[x] = new DrawVoxel**[gridSize.getY()];

		for (int y = 0; y < gridSize.getY(); ++y)
		{
			dv[x][y] = new DrawVoxel*[gridSize.getZ()];

			// Creamos los Voxeles
			for (int z = 0; z < gridSize.getZ(); ++z)
			{
				if (vm.getVoxels()[x][y][z].getType() == type)
				{
					dv[x][y][z] = new DrawVoxel(vm.getVoxels()[x][y][z]);

					dv[x][y][z]->drawIt();
				}
			}
		}
	}
}

GEO::DrawVoxelModel::~DrawVoxelModel()
{
	for (int x = 0; x < vm.getGridSize().getX(); ++x)
		for (int y = 0; y < vm.getGridSize().getY(); ++y)
			for (int z = 0; z < vm.getGridSize().getZ(); ++z)
			{
				delete dv[x][y][z];
			}
}
