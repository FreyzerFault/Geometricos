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


GEO::VoxelModel::VoxelModel(TriangleModel& triModel, double voxelSize) : VoxelGrid(voxelSize, triModel.getAABB()), triModel(&triModel)
{
	// Primero le generamos los Tris porque no son necesarios hasta ahora para agilizar calculos
	triModel.generateTris();
	
	for (int x = 0; x < gridSize.getX(); ++x)
	for (int y = 0; y < gridSize.getY(); ++y)
	for (int z = 0; z < gridSize.getZ(); ++z)
	{
		// Comprueba por cada triangulo de la malla si intersecta
		grid[x][y][z].checkTris(triModel);

		switch (grid[x][y][z].getType())
		{
		case TypeVoxel::out:
			whiteVoxels.push_back(&grid[x][y][z]);
			break;
		case TypeVoxel::intersect:
			greyVoxels.push_back(&grid[x][y][z]);
			break;
		case TypeVoxel::in:
			blackVoxels.push_back(&grid[x][y][z]);
			break;
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