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


bool GEO::Vertex::convex() const
{
	// El vertice debe estar a la izquierda de i+1 -> i-1
	const Vertex nextVertex(next());
	const Vertex previousVertex(previous());

	return left(nextVertex,previousVertex);
}

bool GEO::Vertex::concave() const
{
	return !convex();
}


GEO::Vertex GEO::Vertex::next() const
{
	return _polygon->next(_position);
}

GEO::Vertex GEO::Vertex::previous() const
{
	return _polygon->previous(_position);
}

GEO::SegmentLine GEO::Vertex::nextEdge() const
{
	// A partir de dos Point de el this y el next()
	return {getPoint(), next().getPoint()};
}

GEO::SegmentLine GEO::Vertex::previousEdge() const
{
	return {previous().getPoint(), getPoint()};
}

void GEO::Vertex::out() const
{
	Point::out();
	std::cout << "Position: " <<  std::to_string(_position);
}



