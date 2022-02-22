
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
	static std::string folderName = "Polygon/";
	std::ifstream is(folderName + filename + ".txt");
	if (!is.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para crear el Poligono" << std::endl;

	std::string line;
	std::getline(is, line);
	
	while (std::getline(is, line))
	{
		// Formato: x;y

		if (!std::isdigit(line[0]) && line.find(';'))
			std::cout << "Formato de archivo de Poligono erroneo (" + line + ")" << std::endl;

		Point p(std::stod(line.substr(0, line.find(';'))), std::stod(line.substr(line.find(';') + 1)));

		add(p);
	}

	is.close();
}

GEO::Polygon::~Polygon()
= default;

bool GEO::Polygon::add(Vertex & vertex)
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
		return {};
	}
}

GEO::Point* GEO::Polygon::intersectionPoint(const SegmentLine& segment)
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(segment))
			return p;
	}
	return nullptr;
}

GEO::Point* GEO::Polygon::intersectionPoint(const RayLine& ray)
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(ray))
			return p;
	}
	return nullptr;
}

GEO::Point* GEO::Polygon::intersectionPoint(const Line& line)
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(line))
			return p;
	}
	return nullptr;
}

bool GEO::Polygon::convex()
{
	// Si todos los vertices son Convexos (a la izquierda de sus vertices adyacentes)
	for (auto vertex : _vertices)
	{
		if (!vertex.convex())
			return false;
	}
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

bool GEO::Polygon::pointInConvexPolygon(GEO::Point& point)
{
	for (int i = 0; i < getNumVertices(); ++i)
	{
		Vertex* v0 = &_vertices[i % getNumVertices()];
		Vertex* v1 = &_vertices[i+1 % getNumVertices()];

		// Si el punto no esta a la izquierda y no esta en mitad de la arista no esta contenido en el poligono
		if (!point.left(*v0,*v1))
			return false;
	}
	return true;
}

void GEO::Polygon::save(const std::string& filename) const
{
	static std::string folderName = "Polygon/";
	std::ofstream os(folderName + filename + ".txt");
	if (!os.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para guardar el Poligono" << std::endl;

	for (auto vertex : _vertices)
	{
		os << std::to_string(vertex.getX()) + ';' + std::to_string(vertex.getY()) << std::endl;
	}

	os.close();
}

void GEO::Polygon::set(GEO::Vertex& vertex, int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}


