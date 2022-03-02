// ReSharper disable CppClangTidyReadabilityUseAnyofallof
// ReSharper disable CppClangTidyClangDiagnosticSignCompare
#include <iostream>
#include <sstream>
#include <fstream>
#include "Polygon.h"


bool GEO::Polygon::intersectsWithAnySegment(const Vertex& vertex) const
{
	// Ultima linea
	const SegmentLine newEdge(getVertexAt(getNumVertices() - 1), vertex);

	// Todas las arista menos la ultima
	for (int i = 0; i < getNumVertices() - 1; ++i)
	{
		if (newEdge.segmentIntersection(_vertices[i].nextEdge()))
			return true;
	}

	return false;
}

GEO::Polygon::Polygon(std::vector<Vertex> vertices): _vertices(std::move(vertices))
{
}

GEO::Polygon::Polygon(const Polygon& orig)
{
	for (const Vertex& vertex : orig._vertices)
	{
		add(vertex);
	}
}

GEO::Vertex GEO::Polygon::getVertexAt(const int pos) const
{
	if (pos >= 0 && pos < _vertices.size()) 
		return _vertices[pos];

	return {};
}

GEO::SegmentLine GEO::Polygon::getEdge(const int pos) const
{
	return {getVertexAt(pos), getVertexAt((pos + 1) % _vertices.size())};
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

bool GEO::Polygon::add(const Vertex & vertex)
{
	const int index = _vertices.size();

	if (intersectsWithAnySegment(vertex)) return false;

	_vertices.push_back(vertex);
	_vertices[index].setPolygon(this);
	_vertices[index].setPosition(index);

	return true;
}

bool GEO::Polygon::add(const GEO::Point & point)
{
	return this->add(Vertex(point));
}


GEO::Point* GEO::Polygon::intersectionPoint(const SegmentLine& segment) const
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(segment))
			return p;
	}
	return nullptr;
}

GEO::Point* GEO::Polygon::intersectionPoint(const RayLine& ray) const
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(ray))
			return p;
	}
	return nullptr;
}

GEO::Point* GEO::Polygon::intersectionPoint(const Line& line) const
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		SegmentLine edge = getEdge(i);
		if (Point* p = edge.intersectionPoint(line))
			return p;
	}
	return nullptr;
}

bool GEO::Polygon::convex() const
{
	// Si todos los vertices son Convexos (a la izquierda de sus vertices adyacentes)
	for (const auto& vertex : _vertices)
	{
		if (!vertex.convex())
			return false;
	}
	return true;
}

bool GEO::Polygon::concave() const
{
	return !convex();
}


GEO::Vertex GEO::Polygon::next(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index + 1) % _vertices.size()];
	}

	return {};
}

void GEO::Polygon::out() const
{
	for (auto& _vertice : _vertices)
	{
		_vertice.out();
	}
}

GEO::Vertex GEO::Polygon::previous(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index - 1 + _vertices.size()) % _vertices.size()];
	}

	return {};
}

GEO::Polygon& GEO::Polygon::operator=(const Polygon &polygon)
{
	if (this != &polygon)
	{
		this->_vertices = polygon._vertices;
	}

	return *this;
}

bool GEO::Polygon::pointInConvexPolygon(const GEO::Point& point) const
{
	for (int i = 0; i < getNumVertices(); ++i)
	{
		const Vertex* v0 = &_vertices[i % getNumVertices()];
		const Vertex* v1 = &_vertices[i+1 % getNumVertices()];

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

	for (const auto& vertex : _vertices)
	{
		os << std::to_string(vertex.getX()) + ';' + std::to_string(vertex.getY()) << std::endl;
	}

	os.close();
}

void GEO::Polygon::set(GEO::Vertex& vertex, const int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}


