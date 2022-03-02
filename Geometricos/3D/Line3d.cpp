#include <iostream>
#include "limits.h"
#include <cmath>
#include "BasicGeom.h"
#include "Line3d.h"

GEO::Line3d::Line3d()
{
}

GEO::Line3d::Line3d(Vec3D & orig, Vec3D & dest)
	: Edge3d(orig, dest)
{
}

GEO::Line3d::Line3d(const Line3d & line)
	: Edge3d(line)
{
}

GEO::Line3d::~Line3d()
{
}


double GEO::Line3d::distance(Line3d & line)
{
	//XXXX
    
    return 0;
}

GEO::Line3d GEO::Line3d::normalLine(Vec3D & point)
{
    //XXXX
    
	return Line3d();
}

double GEO::Line3d::distance(Vec3D& p){
    
    ///XXXX
    return 0;
}

GEO::Line3d & GEO::Line3d::operator=(const Line3d & line)
{
	if (this != &line)
	{
		Edge3d::operator=(line);
	}

	return *this;
}

void GEO::Line3d::out()
{
	std::cout << "Line->Origin: ";
	_orig.out();
	std::cout << "Line->Destination: ";
	_dest.out();
}

