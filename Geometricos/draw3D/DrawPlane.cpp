#include "DrawPlane.h"

#include "BasicGeom.h"

using namespace GEO::BasicGeom;

GEO::DrawPlane::DrawPlane (const Plane &plane): Draw(), dt (plane){

	// Tomamos dos vectores perpendiculares del plano y los alargamos al INFINITO
	const Vec3D perpendicular = plane.getV().cross(plane.getNormal());

	const Vec3D a = plane.getP() + perpendicular * INFINITO;
	const Vec3D b = plane.getP() - perpendicular * INFINITO;
	const Vec3D c = plane.getP() + plane.getV() * INFINITO;
	const Vec3D d = plane.getP() - plane.getV() * INFINITO;

	_vertices.emplace_back(a.getX(), a.getY(), a.getZ());
	_vertices.emplace_back(b.getX(), b.getY(), b.getZ());
	_vertices.emplace_back(c.getX(), c.getY(), c.getZ());
	_vertices.emplace_back(d.getX(), d.getY(), d.getZ());

	const Vec3D n = plane.getNormal();

	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());
	_normals.emplace_back(n.getX(), n.getY(), n.getZ());

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(3);

	buildVAO ();
	
}


void GEO::DrawPlane::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawPlane::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::PLAIN);
	GEO::Scene::getInstance ()->addModel ( this );
	
}

