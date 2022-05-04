#include "DrawTDelaunay.h"

GEO::DrawTDelaunay::DrawTDelaunay(const TDelaunay& delaunay)
	: delaunay(delaunay), drawTriangles(new Draw()), drawLines(new Draw())
{
	const std::vector<Triangle> tris = delaunay.getFaces();
	for (const auto& tri : tris)
	{
		drawTriangles->addVertices({
			{tri.getA().getX(), tri.getA().getY(), 0},
			{tri.getB().getX(), tri.getB().getY(), 0},
			{tri.getC().getX(), tri.getC().getY(), 0},
		});
		drawLines->addVertices({
			{tri.getA().getX(), tri.getA().getY(), 0},
			{tri.getB().getX(), tri.getB().getY(), 0},
			{tri.getC().getX(), tri.getC().getY(), 0},
		});
	}
	drawTriangles->addSequencialIndices(drawTriangles->getNumVertices());
	drawTriangles->addDefaultNormals(drawTriangles->getNumVertices());
	drawLines->addSequencialIndices(drawTriangles->getNumVertices());
	drawLines->addDefaultNormals(drawTriangles->getNumVertices());

	drawTriangles->buildVAO();
	drawLines->buildVAO();
}

std::pair<GEO::Draw*, GEO::Draw*> GEO::DrawTDelaunay::drawIt(TypeColor triColor, TypeColor lineColor) const
{
	drawTriangles->setColorActivo(triColor);
	drawLines->setColorActivo(lineColor);
	return drawIt();
}

std::pair<GEO::Draw*, GEO::Draw*> GEO::DrawTDelaunay::drawIt() const
{
	drawTriangles->setShaderProgram("algeom");
	drawTriangles->setDrawMode(TypeDraw::PLAIN);
	Scene::getInstance()->addModel(drawTriangles);
	drawLines->setShaderProgram("algeom");
	drawLines->setDrawMode(TypeDraw::WIREFRAME);
	Scene::getInstance()->addModel(drawLines);

	return std::make_pair(drawTriangles, drawLines);
}
