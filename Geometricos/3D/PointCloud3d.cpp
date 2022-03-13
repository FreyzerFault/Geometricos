#include <cmath>
#include <cinttypes>
#include <sstream>
#include <fstream>
#include <vector>
#include "BasicGeom.h"
#include "PointCloud3D.h"

#include <iostream>
#include <glm/ext/scalar_constants.hpp>

using namespace GEO::BasicGeom;


GEO::PointCloud3D::PointCloud3D() 
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO) 
{
}

GEO::PointCloud3D::PointCloud3D (std::vector<Vec3D> pointCloud):_points(std::move(pointCloud)),
																_maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO){}

GEO::PointCloud3D::PointCloud3D(const std::string& filename)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	auto splitBySemicolon = [this](const std::string& string) -> std::vector<std::string>
	{
		std::stringstream ss(string);
		std::vector<std::string> result;

		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ';');
			result.push_back(substr);
		}

		return result;
	};

	std::string currentLine; 				// Línea actual del fichero.
	std::ifstream inputStream;				// Flujo de entrada.
	inputStream.open(filename.c_str());

	if (!inputStream.good())
		std::cout << "No se ha podido cargar una Nube de Puntos porque no se abre el fichero " + filename << std::endl;

	while (std::getline(inputStream, currentLine))
	{
		std::vector<std::string> coord = splitBySemicolon(currentLine);

		if (coord.size() == 3)
		{
			try {
				this->addPoint(Vec3D(std::stod(coord[0]), std::stod(coord[1]), std::stod(coord[2])));
			}
			catch (const std::exception& excep)
			{
				inputStream.close();

				throw excep;
			}
		}
	}
	inputStream.close();// Cerramos fichero.
}

GEO::PointCloud3D::PointCloud3D(int size, double max_x, double max_y, double max_z)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		const double x = static_cast <double> (rand()) / (RAND_MAX / (max_x * 2.0)) - max_x;
		const double y = static_cast <double> (rand()) / (RAND_MAX / (max_y * 2.0)) - max_y;
		const double z = static_cast <double> (rand()) / (RAND_MAX / (max_z * 2.0)) - max_z;

		this->addPoint(Vec3D(x,y,z));
		--size;
	}
}

GEO::PointCloud3D::PointCloud3D(int size, double radius)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		const double theta = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX)) * 2.0 * glm::pi<double>();
		const double phi = std::acos(1.0 - 2.0 * static_cast <double> (rand()) / (static_cast <double> (RAND_MAX)));
		const double x = std::sin(phi) * std::cos(theta);
		const double y = std::sin(phi) * std::sin(theta);
		const double z = std::cos(phi);

		const double r = radius * std::sqrt(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX)));

		this->addPoint(Vec3D(r * x, r * y, r * z));
		--size;
	}
}

void GEO::PointCloud3D::addPoint(const Vec3D& p)
{
	_points.push_back(p);
	this->updateMaxMin(_points.size() - 1);
}

GEO::AABB GEO::PointCloud3D::getAABB()
{
	return {_minPoint, _maxPoint};
}


GEO::Vec3D GEO::PointCloud3D::getPoint(int pos) const
{
	if (pos >= 0 && (pos < _points.size())) {
		return _points[pos];
	}
	return {};
}

GEO::PointCloud3D& GEO::PointCloud3D::operator=(const PointCloud3D & pointCloud)
{
	if (this != &pointCloud)
	{
		_points = pointCloud._points;
		_maxPoint = pointCloud._maxPoint;
		_minPoint = pointCloud._minPoint;
	}

	return *this;
}

void GEO::PointCloud3D::save(const std::string & filename) const
{
	std::ofstream file(filename);
	if (!file.good())
		std::cout << "No se ha podido guardar una Nube de Puntos porque no se pudo abrir el archivo " + filename << std::endl;;

	for (const auto& p : _points)
	{
		file << p.getX() << ";" << p.getY() << ";" << p.getZ() << std::endl;
	}

	file.close();
}


void GEO::PointCloud3D::updateMaxMin(int index)
{
	const Vec3D point = _points[index];

	if (point.getX() < _minPoint.getX()) { _minPoint.setX(point.getX()); _minPointIndex.setX(index); }
	if (point.getY() < _minPoint.getY()) { _minPoint.setY(point.getY()); _minPointIndex.setY(index); }
	if (point.getZ() < _minPoint.getZ()) { _minPoint.setZ(point.getZ()); _minPointIndex.setZ(index); }

	if (point.getX() > _maxPoint.getX()) { _maxPoint.setX(point.getX()); _maxPointIndex.setX(index); }
	if (point.getY() > _maxPoint.getY()) { _maxPoint.setY(point.getY()); _maxPointIndex.setY(index); }
	if (point.getZ() > _maxPoint.getZ()) { _maxPoint.setZ(point.getZ()); _maxPointIndex.setZ(index); }
}


void GEO::PointCloud3D::getMostDistanced (int &a, int &b){
	//TODO
	a=0; b=0;
}
