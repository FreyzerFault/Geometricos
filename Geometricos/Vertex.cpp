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
= default;

bool GEO::Vertex::convex()
{
	// El vertice debe estar a la izquierda de i+1 -> i-1
	Vertex nextVertex(next());
	Vertex previousVertex(previous());

	return left(nextVertex,previousVertex);
}

bool GEO::Vertex::concave()
{
	return !convex();
}


GEO::Vertex GEO::Vertex::next() const
{
	return _polygon->next(_position);
}

GEO::SegmentLine GEO::Vertex::nextEdge()
{
	// A partir de dos Point de el this y el next()
	return {getPoint(), next().getPoint()};
}

GEO::Vertex& GEO::Vertex::operator=(const Vertex & vertex)
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

GEO::Vertex GEO::Vertex::previous() const
{
	return _polygon->previous(_position);
}


