
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Polygon.h"


GEO::Polygon::Polygon()
{
}

GEO::Polygon::Polygon(const Polygon& PolygonGeo)
{
	_vertices = std::vector<Vertex>(PolygonGeo._vertices);
}

GEO::Polygon::Polygon(std::vector<Vertex>& vertices)
{
	_vertices = std::vector<Vertex>(vertices);
}

GEO::SegmentLine GEO::Polygon::getEdge(int i)
{
	return SegmentLine(getVertexAt(i), getVertexAt((i + 1) % _vertices.size()));
}

GEO::Polygon::Polygon(const std::string & filename)
{
	//XXXX
	
}

GEO::Polygon::~Polygon()
{
}

bool GEO::Polygon::add(GEO::Vertex & vertex)
{
	int index = _vertices.size();

	//if (intersectsWithAnySegment(vertex)) return false;

	_vertices.push_back(vertex);
	_vertices[index].setPolygon(this);
	_vertices[index].setPosition(index);

	return true;
}

bool GEO::Polygon::add(GEO::Point & point)
{
	Vertex vertex(point);

	return this->add(vertex);
}

GEO::Vertex GEO::Polygon::getVertexAt(int pos)
{
	if (pos >= 0 && pos < _vertices.size()) 
	{
		return _vertices[pos];
	}
	else 
	{
		return Vertex();
	}
}

bool GEO::Polygon::convex()
{
	//XXXX
	return true;
}


GEO::Vertex GEO::Polygon::next(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index + 1) % _vertices.size()];
	}

	return Vertex();
}

void GEO::Polygon::out()
{
	for (int i = 0; i < _vertices.size(); i++) {
		_vertices[i].out();
	}
}

GEO::Vertex GEO::Polygon::previous(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index - 1 + _vertices.size()) % _vertices.size()];
	}

	return Vertex();
}

GEO::Polygon& GEO::Polygon::operator=(const Polygon &polygon)
{
	if (this != &polygon)
	{
		this->_vertices = polygon._vertices;
	}

	return *this;
}

bool GEO::Polygon::pointInConvexPolygonGeo(GEO::Point& point)
{
	//XXXX
	return true;
}

void GEO::Polygon::save(const std::string& filename)
{
	//XXXX
}

void GEO::Polygon::set(GEO::Vertex& vertex, int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}


