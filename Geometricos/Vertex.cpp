#include <iostream>
#include <string>
#include "Polygon.h"
#include "Vertex.h"


GEO::Vertex::Vertex()
	: Point()
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}


GEO::Vertex::Vertex(const Point & point, Polygon* polygon, int pos)
	: Point(point)
{
	_position = pos;
	_polygon = polygon;
}

GEO::Vertex::Vertex(const Point& point)
	: Point(point)
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

GEO::Vertex::~Vertex()
{
}

bool GEO::Vertex::convex()
{
	//XXXX

	return false;
}

bool GEO::Vertex::concave()
{
    //XXXX
	return 0;
}


GEO::SegmentLine GEO::Vertex::nextEdge()
{
	//XXXX
	return SegmentLine();
}

GEO::Vertex & GEO::Vertex::operator=(const Vertex & vertex)
{
	if (this != &vertex)
	{
		Point::operator=(vertex);
		this->_polygon = vertex._polygon;
		this->_position = vertex._position;
	}

	return *this;
}


GEO::SegmentLine GEO::Vertex::previousEdge()
{
	//XXXX
	return SegmentLine();
}


void GEO::Vertex::out()
{
	Point::out();
	std::cout << "Position: " <<  std::to_string(_position);
}


