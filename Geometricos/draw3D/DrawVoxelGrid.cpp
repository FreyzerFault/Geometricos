#include "DrawVoxelGrid.h"

#include "Scene.h"
#include "Voxel.h"

GEO::DrawVoxelGrid::DrawVoxelGrid(const VoxelGrid& grid) : Draw(), grid(grid)
{
	// Por cada AABB cogemos sus vertices y los concatenamos
	const Vec3D gridSize = grid.getGridSize();
	_vertices.reserve(3 * 12 * gridSize.getX() * gridSize.getY() * gridSize.getZ());
	for (int x = 0; x < gridSize.getX(); ++x)
	for (int y = 0; y < gridSize.getY(); ++y)
	for (int z = 0; z < gridSize.getZ(); ++z)
	{
		Voxel& voxel = *grid.getVoxel(x,y,z);
		auto aabbVerts = voxel.getAABBVertices();
		_vertices.insert(_vertices.end(), aabbVerts.begin(), aabbVerts.end()) ;
	}

	addSequencialIndices(_vertices.size());
	addDefaultNormals(_vertices.size());
	
	buildVAO();
}

void GEO::DrawVoxelGrid::drawIt()
{
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::WIREFRAME);
	Scene::getInstance()->addModel(this);
}

void GEO::DrawVoxelGrid::drawIt(TypeColor color)
{
	setColorActivo(color);
	drawIt();
}
