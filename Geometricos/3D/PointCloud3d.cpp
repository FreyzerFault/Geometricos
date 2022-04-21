#include <cmath>
#include <cinttypes>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <glm/ext/scalar_constants.hpp>
#include <vector>
#include "BasicGeom.h"
#include "PointCloud3D.h"


using namespace GEO::BasicGeom;

namespace fs = std::filesystem;


static const std::string pcPath = "PointCloud/";


GEO::PointCloud3D::PointCloud3D() 
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO) 
{
}

GEO::PointCloud3D::PointCloud3D (std::vector<Vec3D> pointCloud):_points(std::move(pointCloud)),
	_maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	for (int i = 0; i < _points.size(); i++)
		updateMaxMin(i);
}

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

	// Path para detectar la extension
	fs::path filePath(pcPath + filename);
	
	if (filePath.extension() == ".txt")
	{
		std::ifstream inputStream;
		std::string currentLine;
		inputStream.open(filePath);

		if (!inputStream.good())
			std::cout << "No se ha podido cargar una Nube de Puntos porque no se abre el fichero " + filename << std::endl;

		while (std::getline(inputStream, currentLine))
		{
			std::vector<std::string> coords = splitBySemicolon(currentLine);

			if (coords.size() == 3)
			{
				try {
					this->addPoint(Vec3D(std::stod(coords[0]), std::stod(coords[1]), std::stod(coords[2])));
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
	else if (filePath.extension() == ".ply")
	{
		const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
		
		if (pcl::io::loadPLYFile<pcl::PointXYZ>(filePath.string(), *cloud) == -1)
		{
			PCL_ERROR(("No se pudo leer el archivo " + filePath.filename().string()).c_str());
			throw std::runtime_error("No se pudo leer el archivo " + filePath.filename().string());
		}
		std::cout << "Se ha cargado una Nube de Puntos con PCL \"" << filename << "\"" << std::endl;
		
		_points.reserve(cloud->size());
		_pclPoints = cloud->points;
	}
}

GEO::PointCloud3D::PointCloud3D(int size, double max_x, double max_y, double max_z, const Vec3D& center)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		const double x = static_cast <double> (rand()) / (RAND_MAX / (max_x * 2.0)) - max_x;
		const double y = static_cast <double> (rand()) / (RAND_MAX / (max_y * 2.0)) - max_y;
		const double z = static_cast <double> (rand()) / (RAND_MAX / (max_z * 2.0)) - max_z;

		this->addPoint(Vec3D(x + center.getX(),y + center.getY(),z + center.getZ()));
		--size;
	}
}

GEO::PointCloud3D::PointCloud3D(int size, double radius, const Vec3D& center)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		// Coordenadas polares
		const double theta = (double)rand() / (RAND_MAX) * 2.0 * glm::pi<double>();
		const double phi = std::acos( 1.0 - 2.0 * (double)rand() / RAND_MAX );
		const double x = std::sin(phi) * std::cos(theta);
		const double y = std::sin(phi) * std::sin(theta);
		const double z = std::cos(phi);

		// Radio aleatorio con una distribucion mas concentrada en el centro por el sqrt()
		const double r = radius * std::sqrt( rand() / (double)RAND_MAX );

		this->addPoint(Vec3D(r*x + center.getX(), r*y + center.getY(), r*z + center.getZ()));
		--size;
	}
}

GEO::PointCloud3D::PointCloud3D(int size, const AABB& aabb)
{

	_points = std::vector<Vec3D>();

	const Vec3D max = aabb.getMax() - aabb.getCenter();
	const Vec3D center = aabb.getCenter();

	while (size > 0)
	{
		const double x = static_cast <double> (rand()) / (RAND_MAX / (max.getX() * 2.0)) - max.getX() + center.getX();
		const double y = static_cast <double> (rand()) / (RAND_MAX / (max.getY() * 2.0)) - max.getY() + center.getY();
		const double z = static_cast <double> (rand()) / (RAND_MAX / (max.getZ() * 2.0)) - max.getZ() + center.getZ();

		Vec3D point(x,y,z);

		this->addPoint(point);
		--size;
	}
}

GEO::PointCloud3D::PointCloud3D(int n, int k, double maxRegion)
{
	if (k > n)
		throw std::runtime_error ("Se intenta crear una Nube de Puntos con K clusteres > N puntos/cluster");

	// Creamos k Clusteres
	_points.reserve(n*k);
	for (int i = 0; i < k; ++i)
	{
		// Centro del cluster:
		const double x = rand() / (double)RAND_MAX * maxRegion;
		const double y = rand() / (double)RAND_MAX * maxRegion;
		const double z = rand() / (double)RAND_MAX * maxRegion;
		Vec3D center(x,y,z);

		// Radio [1,2]:
		const double radius = rand() / (double)RAND_MAX * 1 + 1;

		// Creamos la Nube de Puntos
		PointCloud3D pc(n, radius, center);

		// Concatenamos los puntos generados a los anteriores
		std::vector<Vec3D> points = pc.getPoints();
		_points.insert(_points.end(), points.begin(), points.end());
	}
}

void GEO::PointCloud3D::addPoint(const Vec3D& p)
{
	_points.push_back(p);
	this->updateMaxMin(_points.size() - 1);
}

GEO::AABB GEO::PointCloud3D::getAABB() const
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

pcl::PointXYZ GEO::PointCloud3D::getPCLPoint(int pos) const
{
	if (pos >= 0 && (pos < _pclPoints.size())) {
		return _pclPoints[pos];
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

// Struct para escribir doubles con coma en vez de punto
struct Comma final : std::numpunct<char>
{
	char do_decimal_point() const override { return ','; }
};

void GEO::PointCloud3D::save(const std::string & filename) const
{
	std::ofstream file(pcPath + filename + ".txt");
	file.imbue(std::locale(std::locale::classic(), new Comma));
	if (!file.good())
		std::cout << "No se ha podido guardar una Nube de Puntos porque no se pudo abrir el archivo " + filename << std::endl;;

	for (const auto& p : _points)
	{
		file << std::to_string(p.getX()) << ";" << std::to_string(p.getY()) << ";" << std::to_string(p.getZ()) << std::endl;
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


void GEO::PointCloud3D::getMostDistanced (int &a, int &b) const
{
	a = 0; b = 0;
	// Mas alejado del centro y mas cercano al centro
	/*const Vec3D center = getAABB().getCenter();
	Vec3D max(center);
	Vec3D min(center + BasicGeom::BIGNUM);
	for (const Vec3D& point : _points)
	{
		if ((point - center).module() > (max - center).module())
			max = point;
		if ((point - center).module() < (min - center).module())
			min = point;
	}

	for (int i = 0; i < _points.size(); i++)
	{
		const Vec3D& point = _points[i];
		if (point == max)
			a = i;
		if (point == min)
			b = i;
	}*/

	double maxDistance = 0;
	// Mas alejados entre si
	for (int i = 0; i < _points.size(); i++)
	{
		for (int j = 0; j < _points.size(); j++)
		{
			const double d = (_points[i] - _points[j]).module();
			if (d > maxDistance)
			{
				a = i; b = j;
				maxDistance = d;
			}
		}
	}
}

void GEO::PointCloud3D::getMaxPoints(Vec3D& maxX, Vec3D& maxY, Vec3D& maxZ) const
{
	maxX.setX(-BasicGeom::BIGNUM);
	maxY.setY(-BasicGeom::BIGNUM);
	maxZ.setZ(-BasicGeom::BIGNUM);

	for (const Vec3D& point : _points)
	{
		if (point.getX() > maxX.getX())
			maxX = point;
		if (point.getY() > maxY.getY())
			maxY = point;
		if (point.getZ() > maxZ.getZ())
			maxZ = point;
	}
}

void GEO::PointCloud3D::getMinPoints(Vec3D& minX, Vec3D& minY, Vec3D& minZ) const
{
	minX.setX(BasicGeom::BIGNUM);
	minY.setY(BasicGeom::BIGNUM);
	minZ.setZ(BasicGeom::BIGNUM);

	for (const Vec3D& point : _points)
	{
		if (point.getX() < minX.getX())
			minX = point;
		if (point.getY() < minY.getY())
			minY = point;
		if (point.getZ() < minZ.getZ())
			minZ = point;
	}
}

GEO::Vec3D GEO::PointCloud3D::getRandomPoint() const
{
	const int randomIndex = trunc((double)rand() / RAND_MAX * (_points.size() - 1));
	return _points[randomIndex];
}
