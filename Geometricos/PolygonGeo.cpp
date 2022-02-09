
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "PolygonGeo.h"


PolygonGeo::PolygonGeo()
{
}

PolygonGeo::PolygonGeo(const PolygonGeo& PolygonGeo)
{
	_vertices = std::vector<Vertex>(PolygonGeo._vertices);
}

PolygonGeo::PolygonGeo(std::vector<Vertex>& vertices)
{
	_vertices = std::vector<Vertex>(vertices);
}

SegmentLine PolygonGeo::getEdge(int i)
{
	return SegmentLine(getVertexAt(i), getVertexAt((i + 1) % _vertices.size()));
}

PolygonGeo::PolygonGeo(const std::string & filename)
{
	//XXXX
    
}

PolygonGeo::~PolygonGeo()
{
}

bool PolygonGeo::add(Vertex & vertex)
{
	int index = _vertices.size();

	//if (intersectsWithAnySegment(vertex)) return false;

	_vertices.push_back(vertex);
	_vertices[index].setPolygon(this);
	_vertices[index].setPosition(index);

	return true;
}

bool PolygonGeo::add(Point & point)
{
	Vertex vertex(point);

	return this->add(vertex);
}

Vertex PolygonGeo::getVertexAt(int pos)
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

bool PolygonGeo::convex()
{
	//XXXX
	return true;
}



Vertex PolygonGeo::next(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index + 1) % _vertices.size()];
	}

	return Vertex();
}

void PolygonGeo::out()
{
	for (int i = 0; i < _vertices.size(); i++) {
		_vertices[i].out();
	}
}

Vertex PolygonGeo::previous(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index - 1 + _vertices.size()) % _vertices.size()];
	}

	return Vertex();
}

PolygonGeo & PolygonGeo::operator=(const PolygonGeo &polygon)
{
	if (this != &polygon)
	{
		this->_vertices = polygon._vertices;
	}

	return *this;
}

bool PolygonGeo::pointInConvexPolygonGeo(Point& point)
{
    //XXXX
	return true;
}

void PolygonGeo::save(const std::string& filename)
{
	//XXXX
}

void PolygonGeo::set(Vertex& vertex, int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}


