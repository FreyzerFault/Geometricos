
/* 
 * File:   PontCloud3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:36
 */
#pragma once

#include <string>
#include "AABB.h"
//#include "TriangleMesh.h"
#include "Vec3D.h"
namespace GEO
{
	/**
	*	@brief This class represents a set of points distributed in the space.
	*	@author Lidia Mª Ortega Alvarado.
	*/
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

		/**
		*	@brief Deletes the data saved from the convex hull step by step process.
		*/
		//void forgetConvexHullData() { delete _convexHullData; _convexHullData = nullptr; }

		
		// Bounding Box
		AABB getAABB();


		/**
		*	@brief Generates a complete convex hull.
		*/
		//TriangleMesh* getConvexHull();

		/**
		*	@brief Generates the next triangle from the current convex hull.
		*/
		//TriangleMesh* getConvexHullNextTriangle();


		Vec3D getPoint(int pos);
		std::vector<Vec3D> getPoints() { return _points; }
		
		int size() const { return _points.size(); }
		
		PointCloud3D& operator=(const PointCloud3D& pointCloud);

		// Guarda la Nube de Puntos en un archivo con sus coordenadas
		void save(const std::string& filename) const;
		

		// Punto a mas distancia
		void getMostDistanced(int& a, int& b);


	};

}

