#pragma once

#include <string>
#include "AABB.h"
//#include "TriangleMesh.h"
#include "Vec3D.h"
namespace GEO
{
	class PointCloud3D
	{
	protected:
		std::vector<Vec3D> _points;
		Vec3D _maxPoint, _minPoint;				// AABB.
		Vec3D _maxPointIndex, _minPointIndex;	// Indices of those vertices which have the boundary coordinates of the mesh.
		
	protected:
		
		// Toma en cuenta un nuevo punto para actualizar el Maximo y Minimo
		void updateMaxMin(int index);

	public:
		// Nube de Puntos infinita
		PointCloud3D();

		// Puntos en un vector
		PointCloud3D(std::vector<Vec3D> pointCloud);

		// Carga la Nube de un archivo con las coordenadas de cada punto
		PointCloud3D(const std::string& filename);

		// Nube con una distribucion en un cubo
		PointCloud3D(int size, double max_x, double max_y, double max_z);
		
		// Distribucion esferica
		PointCloud3D(int size, double radius);


		PointCloud3D(const PointCloud3D& pointCloud) = default;
		
		virtual ~PointCloud3D() = default;


		void addPoint(const Vec3D& p);

		void clear() { _points.clear(); }

		// Bounding Box
		AABB getAABB();


		// Elimina los datos calculados del Convex Hull
		//void forgetConvexHullData() { delete _convexHullData; _convexHullData = nullptr; }


		// Genera el Convex Hull
		//TriangleMesh* getConvexHull();

		// Genera el siguiente Triangulo del Convex Hull
		//TriangleMesh* getConvexHullNextTriangle();


		Vec3D getPoint(int pos) const;
		std::vector<Vec3D> getPoints() const { return _points; }
		
		int size() const { return _points.size(); }
		
		PointCloud3D& operator=(const PointCloud3D& pointCloud);

		// Guarda la Nube de Puntos en un archivo con sus coordenadas
		void save(const std::string& filename) const;
		

		// Punto a mas distancia
		void getMostDistanced(int& a, int& b);


	};

}

