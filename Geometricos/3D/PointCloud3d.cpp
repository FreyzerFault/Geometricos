#include "PointCloud3D.h"
#include "BasicGeom.h"
#include "VoxelGrid.h"

#include <cinttypes>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm/ext/scalar_constants.hpp>

#include "Voxel.h"
#include <pcl/ModelCoefficients.h>
#include <pcl/ml/kmeans.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

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
		for (pcl::PointXYZ& point : cloud->points)
		{
			addPoint({ point.x, point.y, point.z });
		}
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
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
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

GEO::PointCloud3D::PointCloud3D(int n, int k, double maxRegion, double maxRadius, double minRadius)
	: _maxPoint(menosINFINITO, menosINFINITO, menosINFINITO), _minPoint(INFINITO, INFINITO, INFINITO)
{
	if (k > n)
		throw std::runtime_error ("Se intenta crear una Nube de Puntos con K clusteres > N puntos/cluster");

	// Creamos k Clusteres
	_points.reserve(n*k);
	for (int i = 0; i < k; ++i)
	{
		// Centro del cluster:
		const double x = rand() / (double)RAND_MAX * maxRegion - maxRegion / 2;
		const double y = rand() / (double)RAND_MAX * maxRegion - maxRegion / 2;
		const double z = rand() / (double)RAND_MAX * maxRegion - maxRegion / 2;
		Vec3D center(x,y,z);

		// Radio [1,2]:
		const double radius = rand() / (double)RAND_MAX * maxRadius + minRadius;

		// Creamos la Nube de Puntos
		PointCloud3D pc(n, radius, center);

		// Concatenamos los puntos generados a los anteriores
		std::vector<Vec3D> points = pc.getPoints();
		_points.insert(_points.end(), points.begin(), points.end());
	}
	for (int i = 0; i < _points.size(); ++i)
	{
		updateMaxMin(i);
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
	if (pos >= 0 && (pos < _points.size())) {
		return _points[pos].toPointXYZ();
	}
	return {};
}

std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ>> GEO::PointCloud3D::getPCLPoints() const
{
	std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ>> points;

	for (const Vec3D& point : _points)
	{
		points.emplace_back(point.getX(), point.getY(), point.getZ());
	}

	return points;
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

void GEO::PointCloud3D::save(const std::string & filename, bool usingPCL) const
{
	if (usingPCL)
	{
		pcl::PLYWriter writer;

		// Convierte la Nube a una Nube de PCL
		auto points = getPCLPoints();
		pcl::PointCloud<pcl::PointXYZ> cloudData;
		cloudData.insert(cloudData.begin(), points.begin(), points.end());

		writer.write(pcPath + filename + ".ply", cloudData);
	}
	else
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
}

GEO::Vec3D GEO::PointCloud3D::getCentroid() const
{
	Vec3D centroid(0,0,0);
	for (auto& p : _points)
	{
		centroid = centroid + p;
	}
	
	return centroid / _points.size();
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

void GEO::PointCloud3D::generateVoxelGrid(double voxelSize)
{
	// Solo lo genera si no esta ya generada
	if (voxelGrid != nullptr && BasicGeom::equal(voxelGrid->getVoxelSize(), voxelSize))
		return;

	voxelGrid = new VoxelGrid(voxelSize, *this);
}


void GEO::PointCloud3D::KmeansData::getRandomCentroids(int k, const std::vector<GEO::Vec3D>& points)
{
	std::set<int> pointSelected;
	for (int i = 0; i < k; ++i)
	{
		// Random (que no se repita)
		int index = -1;
		do
		{
			pointSelected.insert(index);
			index = round((double)rand() / (RAND_MAX) * points.size());
		}
		while (pointSelected.find(index) != pointSelected.end());

		centroids[i] = points[index];
	}
}

void GEO::PointCloud3D::KmeansData::updateClusters(const std::vector<GEO::Vec3D>& points)
{
	for (auto && cluster : clusters)
	{
		cluster.clear();
	}

	for (auto && point : points)
	{
		double minDist = INFINITO;
		int bestCluster = 0;

		for (int i = 0; i < centroids.size(); ++i)
		{
			const double dist = point.distance(centroids[i]);

			if (dist < minDist)
			{
				minDist = dist;
				bestCluster = i;
			}
		}

		clusters[bestCluster].addPoint(point);
	}
}

void GEO::PointCloud3D::KmeansData::updateCentroids()
{
	for (int i = 0; i < centroids.size(); ++i)
		if (clusters[i].size() != 0)
			centroids[i] = clusters[i].getCentroid();
}

bool GEO::PointCloud3D::KmeansData::differentCentroids(double error) const
{
	for (int i = 0; i < centroids.size(); ++i)
	{
		if (centroids[i].distance(lastCentroids[i]) > error)
			return true;
	}
	return false;
}

GEO::PointCloud3D::KmeansData GEO::PointCloud3D::kmeans(int k, TypeKmeans type, double error) const
{
	KmeansData data(k);

	switch (type)
	{
	case naive:
		data.getRandomCentroids(k, _points);
		break;

	case grid:
		//generateVoxelGrid();
		if (voxelGrid)
		{
			// Inicializamos los centroides a puntos centrales de los voxeles mas poblados:
			const std::vector<Voxel*> voxels = voxelGrid->voxelsMasPoblados(k);
			for (int i = 0; i < k; ++i)
				data.centroids[i] = voxels[i]->getCenter();
		}
		else
		{
			std::cout << "No se genero el VoxelGrid para hacer el Kmeans con Grid" << std::endl;
		}

		break;

	case pcl:
		data = kmeans_pcl(k);
		break;

	case pcl_kdtree:
		data = kmeans_pcl_kdtree(k);
		break;
	}

	if (type == grid || type == naive)
	{
		// Repetimos el proceso hasta que en una iteracion no se m{odifiquen los centroides mas alla de un error
		do
		{
			// Guardamos la lista de centroides de cada iteracion para comparar con la nueva
			data.lastCentroids = data.centroids;

			// Añadimos el punto al cluster cuyo centroide este mas cerca:
			data.updateClusters(_points);

			// Actualizamos Centroides:
			data.updateCentroids();

			data.iteration++;

		} while (data.differentCentroids(error));
	}

	return data;
}

GEO::PointCloud3D::KmeansData GEO::PointCloud3D::kmeans_pcl(int k) const
{
	KmeansData data(k);

	pcl::Kmeans km(_points.size(), 3);
	km.setClusterSize(k);
	for (const Vec3D& point : _points)
	{
		pcl::Kmeans::Point p;
		p.push_back(point.getX());
		p.push_back(point.getY());
		p.push_back(point.getZ());

		km.addDataPoint(p);
	}

	// Calculo del K-Means
	km.kMeans();

	const pcl::Kmeans::Centroids& centroids = km.get_centroids();

	for (int i = 0; i < k; ++i)
	{
		data.centroids[i] = {centroids[i][0], centroids[i][1], centroids[i][2]};
	}

	// Calculamos para cada punto de la nube cual es su centroide mas cercano
	// y lo metemos en su nube correspondiente
	data.updateClusters(_points);

	return data;
}

GEO::PointCloud3D::KmeansData GEO::PointCloud3D::kmeans_pcl_kdtree(int k) const
{
	const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	for (const Vec3D& point : _points)
	{
		cloud->emplace_back(point.getX(), point.getY(), point.getZ());
	}

	// Creacion del Kdtree
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);

	// Set Parametros
	std::vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
	ec.setClusterTolerance(0.2); // 2cm
	ec.setMinClusterSize(100);
	//ec.setMaxClusterSize(5000);
	ec.setSearchMethod(tree);
	ec.setInputCloud(cloud);

	// K-Means:
	ec.extract(cluster_indices);

	// Writer de los clusters
	pcl::PCDWriter writer;

	int j = 0;
	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
	{
		const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);

		for (const auto& idx : it->indices)
		      cloud_cluster->push_back((*cloud)[idx]);

		cloud_cluster->width = cloud_cluster->size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;
		
		std::cout << "PointCloud representing the Cluster: " << cloud_cluster->size() << " data points." << std::endl;

		/*std::stringstream ss;
		ss << "cloud_cluster_" << j << ".pcd";
		
		writer.write<pcl::PointXYZ>(ss.str(), *cloud_cluster, false);
		j++;*/
	}

	// Conversion a Vec3D
	KmeansData data(cluster_indices.size());
	for (int i = 0; i < cluster_indices.size(); ++i)
	{
		for (const auto& idx : cluster_indices.at(i).indices)
			data.clusters[i].addPoint({(*cloud)[idx].x, (*cloud)[idx].y, (*cloud)[idx].z});
	}
	
	return data;
}

GEO::PointCloud3D::KmeansData& GEO::PointCloud3D::kmeans_progressive(int k, KmeansData& data, TypeKmeans type) const
{
	if (type != naive && type != grid)
	{
		std::cout << "Animacion no implementada" << std::endl;
		return data;
	}

	// Guardamos la lista de centroides de cada iteracion para comparar con la nueva
	data.lastCentroids = data.centroids;

	if (data.iteration == 0)
	{
		// Inicializacion dependiendo de si es Naive o Grid
		if (type == naive)
			// Inicializamos a Centroides random
			data.getRandomCentroids(k, _points);
		else if (type == grid)
		{
			// Inicializamos los centroides a puntos centrales de los voxeles mas poblados:
			data.centroids.clear();
			const auto voxels = voxelGrid->voxelsMasPoblados(k);
			for (const auto& voxel : voxels)
				data.centroids.emplace_back(voxel->getCenter());
			}
	}
	else
		// Recalculamos Centroides:
		data.updateCentroids();

	// Añadimos el punto al cluster cuyo centroide este mas cerca:
	data.updateClusters(_points);

	data.iteration++;

	return data;
}
