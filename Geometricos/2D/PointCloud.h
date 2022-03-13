#pragma once

#include <vector>
#include "Point.h"


namespace GEO
{
	class PointCloud
	{
	protected:
		std::vector<Point> _points;

	public:
		PointCloud() = default;

		// Random puntos en un area de [-(max_x,max_y), (max_x,max_y)]
		PointCloud(int size, double max_x, double max_y);

		// Carga la nube de un fichero con las coordenadas de cada punto
		PointCloud(const std::string& filename);
		
		~PointCloud() = default;

		// Añade un Punto
		void addPoint(Point& p);
		void addPoint(double x, double y);

		// Punto que minimiza la distancia con todos los demas
		Point centralPoint() const;

		// Elimina un punto
		void deletePoint(int index);

		// Puntos maximos en cada coordenada
		void getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y) const;

		// Numero de puntos
		int size() const { return _points.size(); }

		Point getPoint(int position);

		std::vector<Point> getPoints() { return _points; }

		// Guarda las coordenadas de cada punto en un archivo
		void save(const std::string& filename) const;

		PointCloud& operator=(const PointCloud& pointCloud);
	};
	
}

