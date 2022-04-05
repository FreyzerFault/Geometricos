#include "VoxelModel.h"

// CALCULA EL MINIMO COMUN MULTIPLO para sacar el tamaño de la caja de Voxeles
int getMCM(int a, int b)
{
	// Buscamos el mayor numero desde donde empezar
	int mcm = GEO::BasicGeom::max2(a,b);

	int numIteraciones = 0;

	while (true) {
		// Si el resto al dividir por cada numero es 0, es MCM
		if (mcm % a == 0 && mcm % b == 0 && mcm) {
			return mcm;
		}
		if (numIteraciones > 100)
			return GEO::BasicGeom::max2(a,b);
		mcm++;
		numIteraciones++;
	}
}

GEO::VoxelModel::VoxelModel(TriangleModel& triModel, double voxelSize) : triModel(&triModel)
{
	const AABB modelAABB = triModel.getAABB();

	const Vec3D extent = modelAABB.getExtent();

	// Si se pasa de tamaño le cogemos el ceil para no quedarnos cortos
	Vec3D size(std::ceil(extent.getX() / voxelSize), std::ceil(extent.getY() / voxelSize), std::ceil(extent.getZ() / voxelSize));

	for (int x = 0; x < size.getX(); x++)
		for (int y = 0; y < size.getX(); y++)
			for (int z = 0; z < size.getX(); z++)
			{
				Vec3D voxelMin(x,y,z);
				voxelMin = voxelMin * voxelSize;

				Vec3D voxelMax = voxelMin + voxelSize;

				Voxel voxel(voxelMin, voxelMax);
				voxel.getColor();
				voxels.push_back(voxel);
			}
}
