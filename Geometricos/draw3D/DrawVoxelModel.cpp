#include "DrawVoxelModel.h"

GEO::DrawVoxelModel::DrawVoxelModel(VoxelModel vm) : voxelModel(std::move(vm)),
WhiteDraw(new Draw()), BlackDraw(new Draw()), GreyDraw(new Draw()) {

	// BLANCOS
	for (int i = 0; i < voxelModel.getWhiteVoxels().size(); ++i)
	{
		std::vector<Voxel*> voxels = voxelModel.getWhiteVoxels();

		std::vector<glm::vec3> vertices = voxels[i]->getAABBVertices();
		int numVertices = vertices.size();

		WhiteDraw->addVertices(vertices);

		WhiteDraw->addDefaultNormals(numVertices);

		// Añade indices seguidos (0,1,2,3,4,...) hasta el numero de vertices,
		// pero empezando desde el que toca
		WhiteDraw->addSequencialIndices(numVertices, i * numVertices);
	}
	WhiteDraw->buildVAO();

	// GRISES
	for (int i = 0; i < voxelModel.getGreyVoxels().size(); ++i)
	{
		std::vector<Voxel*> voxels = voxelModel.getGreyVoxels();
		
		std::vector<glm::vec3> vertices = voxels[i]->getAABBVertices();
		int numVertices = vertices.size();

		GreyDraw->addVertices(vertices);

		GreyDraw->addDefaultNormals(numVertices);

		// Añade indices seguidos (0,1,2,3,4,...) hasta el numero de vertices,
		// pero empezando desde el que toca
		GreyDraw->addSequencialIndices(numVertices, i * numVertices);
	}
	GreyDraw->buildVAO();

	// NEGROS
	for (int i = 0; i < voxelModel.getBlackVoxels().size(); ++i)
	{
		std::vector<Voxel*> voxels = voxelModel.getBlackVoxels();

		std::vector<glm::vec3> vertices = voxels[i]->getAABBVertices();
		int numVertices = vertices.size();

		BlackDraw->addVertices(vertices);

		BlackDraw->addDefaultNormals(numVertices);

		// Añade indices seguidos (0,1,2,3,4,...) hasta el numero de vertices,
		// pero empezando desde el que toca
		BlackDraw->addSequencialIndices(numVertices, i * numVertices);
	}
	BlackDraw->buildVAO();
}


GEO::Draw* GEO::DrawVoxelModel::drawIt(TypeVoxel type)
{
	switch (type)
	{
	case TypeVoxel::out:
		WhiteDraw->setColorActivo(white);
		WhiteDraw->setShaderProgram ( "algeom" );
		WhiteDraw->setDrawMode(TypeDraw::WIREFRAME );
		Scene::getInstance()->addModel ( WhiteDraw );
		return WhiteDraw;
	case TypeVoxel::intersect:
		GreyDraw->setColorActivo(grey);
		GreyDraw->setShaderProgram ( "algeom" );
		GreyDraw->setDrawMode(TypeDraw::WIREFRAME );
		Scene::getInstance()->addModel ( GreyDraw );
		return GreyDraw;
	case TypeVoxel::in:
		BlackDraw->setColorActivo(black);
		BlackDraw->setShaderProgram ( "algeom" );
		BlackDraw->setDrawMode(TypeDraw::WIREFRAME );
		Scene::getInstance()->addModel ( BlackDraw );
		return BlackDraw;
	}
}

