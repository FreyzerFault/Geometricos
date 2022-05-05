#include "DrawConvexHull3D.h"

#include "Scene.h"
#include "Triangle.h"

GEO::DrawConvexHull3D::DrawConvexHull3D(const ConvexHull3D& convexHull)
	: convexHull(convexHull), drawTriangles(new Draw()), drawLines(new Draw())
{
	const std::vector<Triangle3D>& tris = convexHull.getFaces();
	for (const auto& tri : tris)
	{
		const std::vector<glm::vec3> vertices = {
			{tri.getA().getX(), tri.getA().getY(), tri.getA().getZ()},
			{tri.getB().getX(), tri.getB().getY(), tri.getB().getZ()},
			{tri.getC().getX(), tri.getC().getY(), tri.getC().getZ()},
		};
		Vec3D normal = tri.normal();

		drawTriangles->addVertices(vertices);
		drawLines->addVertices(vertices);

		drawTriangles->addNormal(normal.getX(), normal.getY(), normal.getZ());
		drawLines->addNormal(normal.getX(), normal.getY(), normal.getZ());
	}
	drawTriangles->addSequencialIndices(drawTriangles->getNumVertices());
	drawLines->addSequencialIndices(drawTriangles->getNumVertices());


	drawTriangles->addDefaultNormals(drawTriangles->getNumVertices());
	drawLines->addDefaultNormals(drawTriangles->getNumVertices());

	drawTriangles->buildVAO();
	drawLines->buildVAO();
}

std::pair<GEO::Draw*, GEO::Draw*> GEO::DrawConvexHull3D::drawIt() const
{
	drawTriangles->setShaderProgram("algeom");
	drawTriangles->setDrawMode(TypeDraw::TRANSPARENCY);
	Scene::getInstance()->addModel(drawTriangles);
	drawLines->setShaderProgram("algeom");
	drawLines->setDrawMode(TypeDraw::WIREFRAME);
	Scene::getInstance()->addModel(drawLines);

	return std::make_pair(drawTriangles, drawLines);
}

std::pair<GEO::Draw*, GEO::Draw*> GEO::DrawConvexHull3D::drawIt(TypeColor triColor, TypeColor lineColor) const
{
	drawTriangles->setColorActivo(triColor);
	drawLines->setColorActivo(lineColor);

	drawTriangles->setAmbient(triColor.getVec4());
	drawTriangles->setDiffuse(triColor.getVec4());
	drawTriangles->setEspecular(triColor.getVec4());
	
	return drawIt();
}
