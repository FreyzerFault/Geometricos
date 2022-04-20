#include "VoxelModel.h"

#include <iostream>

#include "TriangleModel.h"

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


GEO::VoxelModel::VoxelModel(TriangleModel& triModel, double voxelSize) : triModel(&triModel), voxelSize(voxelSize)
{
	// Primero le generamos los Tris porque no son necesarios hasta ahora para agilizar calculos
	triModel.generateTris();

	const AABB modelAABB = triModel.getAABB();

	const Vec3D extent = modelAABB.getExtent();

	// Si se pasa de tamaño le cogemos el ceil para no quedarnos cortos
	gridSize = Vec3D(std::ceil(extent.getX() / voxelSize), std::ceil(extent.getY() / voxelSize), std::ceil(extent.getZ() / voxelSize));

	std::cout << "Creando con " << gridSize.getX() << " * "  << gridSize.getY() << " * " << gridSize.getZ() << " voxels.." << std::endl;

	// Reservamos espacio para la Malla 3D:
	voxelGrid = new Voxel**[gridSize.getX()];

	for (int x = 0; x < gridSize.getX(); ++x)
	{
		voxelGrid[x] = new Voxel*[gridSize.getY()];

		for (int y = 0; y < gridSize.getY(); ++y)
		{
			voxelGrid[x][y] = new Voxel[gridSize.getZ()];

			// Creamos los Voxeles
			for (int z = 0; z < gridSize.getZ(); ++z)
			{
				// Esquina inferior del voxel
				Vec3D voxelMin(x,y,z);
				voxelMin = voxelMin * voxelSize + modelAABB.getMin();

				// Esquina superior
				Vec3D voxelMax = voxelMin + voxelSize;
				
				voxelGrid[x][y][z] = Voxel(voxelMin, voxelMax, this);

				// Comprueba por cada triangulo de la malla si intersecta
				voxelGrid[x][y][z].checkTris(triModel);

				switch (voxelGrid[x][y][z].getType())
				{
				case TypeVoxel::out:
					whiteVoxels.push_back(&voxelGrid[x][y][z]);
					break;
				case TypeVoxel::intersect:
					greyVoxels.push_back(&voxelGrid[x][y][z]);
					break;
				case TypeVoxel::in:
					blackVoxels.push_back(&voxelGrid[x][y][z]);
					break;
				}
			}
		}
	}
}


bool GEO::VoxelModel::pointIntoMesh(const Vec3D& point, bool checkTris, bool useRaycast) const
{
	Voxel* v = getVoxel(point);
	if (v == nullptr)
		return false;

	switch (v->getType())
	{
	case TypeVoxel::in:
		return true;
	case TypeVoxel::out:
		return false;
	case TypeVoxel::intersect:

		// Podemos comprobar cada triangulo
		if (checkTris)
		{
			// Usamos el metodo tradicional con raycast para los n triangulos O(n)
			if (useRaycast)
			{
				return triModel->pointIntoMesh(point);
			}

			// Comprobamos que el punto este por detras de todos los Tris del Voxel
			// Si esta por delante de alguno, estara fuera siempre que sea CONVEXO
			for (const Triangle3D* tri : v->getTris())
			{
				if (tri->classify(point) != Triangle3D::NEGATIVE )
					return false; // Si no esta por detras
			}
		}

	// Si esta por detras en TOS
		return true;

	default: 
		return false;
	}
}

GEO::Voxel* GEO::VoxelModel::getVoxel(int x, int y, int z) const
{
	if (x >= gridSize.getX() || y >= gridSize.getY() || z >= gridSize.getZ() || x < 0 || y < 0 || z < 0)
		return nullptr;

	return &voxelGrid[x][y][z];
}

GEO::Voxel* GEO::VoxelModel::getVoxel(const Vec3D& point) const
{
	const AABB aabb = triModel->getAABB();

	if (!aabb.pointInAABB(point))
		return nullptr;

	const Vec3D localPoint = point - aabb.getMin();

	const int x = std::floor(localPoint.getX() / voxelSize);
	const int y = std::floor(localPoint.getY() / voxelSize);
	const int z = std::floor(localPoint.getZ() / voxelSize);

	return &voxelGrid[x][y][z];
}
