#include "DrawVoxelModel.h"

GEO::DrawVoxelModel::DrawVoxelModel(VoxelModel vm) : Draw(), vm(std::move(vm)) {

	const Vec3D gridSize = vm.getGridSize();

	// Reservamos espacio para la Malla 3D:
	WhiteDraw.reserve()[gridSize.getX()];
	GreyDraw = new DrawVoxel [gridSize.getX()];
	BlackDraw = new DrawVoxel [gridSize.getX()];

	for (int x = 0; x < gridSize.getX(); ++x)
	{
		WhiteDraw[x] = new DrawVoxel **[gridSize.getY()];
		GreyDraw[x] = new DrawVoxel **[gridSize.getY()];
		BlackDraw[x] = new DrawVoxel **[gridSize.getY()];

		for (int y = 0; y < gridSize.getY(); ++y)
		{
			WhiteDraw[x][y] = new DrawVoxel * [gridSize.getZ()];

			// Creamos los Voxeles
			for (int z = 0; z < gridSize.getZ(); ++z)
			{
				TypeVoxel type = vm.getVoxels()[x][y][z].getType();
				WhiteDraw[x][y][z] = new DrawVoxel(vm.getVoxels()[x][y][z]);
				WhiteDraw[x][y][z]->drawIt();
			}
		}
	}
}



void GEO::DrawVoxelModel::drawIt(TypeVoxel type)
{
	// Dibujar cada uno de los voxeles del modelo
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PLAIN);
		
	const Vec3D gridSize = vm.getGridSize();

	// Reservamos espacio para la Malla 3D:
	WhiteDraw = new DrawVoxel***[gridSize.getX()];

	for (int x = 0; x < gridSize.getX(); ++x)
	{
		WhiteDraw[x] = new DrawVoxel**[gridSize.getY()];

		for (int y = 0; y < gridSize.getY(); ++y)
		{
			WhiteDraw[x][y] = new DrawVoxel*[gridSize.getZ()];

			// Creamos los Voxeles
			for (int z = 0; z < gridSize.getZ(); ++z)
			{
				if (vm.getVoxels()[x][y][z].getType() == type)
				{
					WhiteDraw[x][y][z] = new DrawVoxel(vm.getVoxels()[x][y][z]);

					WhiteDraw[x][y][z]->drawIt();
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
				delete WhiteDraw[x][y][z];
			}
}
