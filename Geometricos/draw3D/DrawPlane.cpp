#include "DrawPlane.h"

#include "BasicGeom.h"

using namespace GEO::BasicGeom;

GEO::DrawPlane::DrawPlane (const Plane &plane): Draw(), dt (plane){

	// Tomamos dos vectores perpendiculares del plano y los alargamos al INFINITO
	const Vec3D perpendicular = plane.getV().cross(plane.getNormal());

	const Vec3D a = plane.getP() + perpendicular * 4;
	const Vec3D b = plane.getP() - perpendicular * 4;
	const Vec3D c = plane.getP() + plane.getV() * 4;
	const Vec3D d = plane.getP() - plane.getV() * 4;

	_vertices.emplace_back(a.getX(), a.getY(), a.getZ());
	_vertices.emplace_back(b.getX(), b.getY(), b.getZ());
	_vertices.emplace_back(c.getX(), c.getY(), c.getZ());
	_vertices.emplace_back(b.getX(), b.getY(), b.getZ());
	_vertices.emplace_back(a.getX(), a.getY(), a.getZ());
	_vertices.emplace_back(d.getX(), d.getY(), d.getZ());

	const Vec3D n = plane.getNormal();

	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(3);
	_indices.push_back(4);
	_indices.push_back(5);

	buildVAO ();
	
}


void GEO::DrawPlane::drawIt (TypeColor c){
	setColorActivo (c);
	setAmbient(glm::vec4(colorAct.getVec3(), .2f));
	drawIt();
}

void GEO::DrawPlane::drawIt(TypeColor c, TypeDraw typeDraw)
{
	setColorActivo(c);
	setAmbient(glm::vec4(colorAct.getVec3(), .2f));
	drawIt(typeDraw);
}


void GEO::DrawPlane::drawIt (TypeDraw typeDraw){
	setShaderProgram ( "algeom" );
	setDrawMode(typeDraw);
	GEO::Scene::getInstance ()->addModel ( this );
	
}

