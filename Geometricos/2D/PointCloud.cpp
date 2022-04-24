#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <random>
#include "PointCloud.h"

GEO::PointCloud::PointCloud(int size, double max_x, double max_y)
{
	for (int i = 0; i < size; ++i)
	{
		// 2 numeros random [0,1] %
		const double randomX = (double) rand() / (double) RAND_MAX;
		const double randomY = (double) rand() / (double) RAND_MAX;

		// De % al rango en el que se crea la nube de puntos [-max_x, max_x] [-max_y, max_y]
		double x = -max_x + (randomX) * max_x * 2;
		double y = -max_y + (randomY) * max_y * 2;

		_points.emplace_back(x,y);
	}
}

GEO::PointCloud::PointCloud(const std::string& filename)
{
	static std::string folderName = "PointCloud/";
	std::ifstream is(folderName + filename + ".txt");
	if (!is.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para crear la Nube de Puntos" << std::endl;

	std::string line;
	std::getline(is, line);
	
	while (std::getline(is, line))
	{
		// Formato: x;y

		if (!std::isdigit(line[0]) && line.find(';'))
			std::cout << "Formato de archivo de Bezier erroneo (" + line + ")" << std::endl;

		const double x = std::stod(line.substr(0, line.find(';')));
		const double y = std::stod(line.substr(line.find(';') + 1));

		addPoint(x, y);
	}

	is.close();
}

void GEO::PointCloud::addPoint(Point& p)
{
	_points.push_back(p);
}

void GEO::PointCloud::addPoint(double x, double y)
{
	_points.emplace_back(x, y);
}

GEO::Point GEO::PointCloud::centralPoint() const
{
	Point* central = nullptr;
	double minAcumDistances = BasicGeom::INFINITO;
	for (auto p0 : _points)
	{
		// Acumula las distancias con cada otra punto de la nube
		double acumDistances = 0;
		for (const auto& p1 : _points)
		{
			acumDistances += p0.distPoint(p1);
		}
		// Si es la menor suma de distancias sera el mas central
		if (acumDistances < minAcumDistances)
		{
			central = &p0;
			minAcumDistances = acumDistances;
		}
	}
	if (central)
		return *central;
	
	return {};
}

void GEO::PointCloud::getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y) const
{
	if (_points.empty())
		return;

	// Empezamos con todos al primero
	minPoint_x = minPoint_y = maxPoint_x = maxPoint_y = _points[0];

	// Por cada punto comprobamos si mejora algunos de los 4
	for (const Point& p : _points)
	{
		if (p.getX() < minPoint_x.getX())
			minPoint_x = p;
		if (p.getX() > maxPoint_x.getX())
			maxPoint_x = p;
		if (p.getY() < minPoint_y.getY())
			minPoint_y = p;
		if (p.getY() > maxPoint_y.getY())
			maxPoint_y = p;
	}
}

void GEO::PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}


GEO::Point GEO::PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return {};
}

GEO::PointCloud & GEO::PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void GEO::PointCloud::save(const std::string& filename) const
{
	static std::string folderName = "PointCloud/";
	std::ofstream os(folderName + filename + ".txt");
	if (!os.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para guardar la Nube de Puntos" << std::endl;

	for (auto point : _points)
	{
		os << std::to_string(point.getX()) + ';' + std::to_string(point.getY()) << std::endl;
	}

	os.close();
}
