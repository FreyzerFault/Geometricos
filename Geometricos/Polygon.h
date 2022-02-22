
/* 
 * File:   PolygonGeo.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 10:20
 */

#ifndef PolygonGeo_H
#define PolygonGeo_H


#include <vector>
#include <iostream>
#include "Line.h"
#include "RayLine.h"
#include "Vec2D.h"
#include "Vertex.h"

namespace GEO
{
	class Polygon
	{
	protected:
		std::vector<Vertex> _vertices;
		
		/**
		*	@brief Checks if a vertex (not included in the PolygonGeo) creates a segment with the last vertex that collides with any other segment.
		*/
		bool intersectsWithAnySegment(Vertex& vertex);

	public:
		/**
		*	@brief Default empty constructor.
		*/
		Polygon();

		/**
		*	@brief Constructor.
		*/
		Polygon(std::vector<Vertex>& vertices);

		/**
		*	@brief Copy constructor.
		*/
		Polygon(const Polygon& PolygonGeo);

		/**
		*	@brief Constructor of a PolygonGeo from a file.
		*/
		Polygon(const std::string& filename);

		/**
		*	@brief Destructor.
		*/
		~Polygon();

		/**
		*	@brief Adds the vertex in the last position (if it doesn't intersect with any other segment).
		*/
		bool add(Vertex& vertex);

		/**
		*	@brief Adds the point in the last position (if it doesn't intersect with any other segment).
		*/
		bool add(Point& point);

		/**
		*	@brief Checks if the PolygonGeo is convex.
		*/
		bool convex();

		/**
		*	@brief Returns the edge i.
		*/
		SegmentLine getEdge(int i);

		/**
		*	@brief Returns the number of vertices of the PolygonGeo.
		*/
		int getNumVertices() { return _vertices.size(); }

		/**
		*	@brief Returns the vertex at an index.
		*/
		Vertex getVertexAt(int pos);

		
		// Punto de intersseccion con un segmento, linea o rayo
		Point* intersectionPoint(const SegmentLine& segment);
		Point* intersectionPoint(const RayLine& ray);
		Point* intersectionPoint(const Line& line);
		
		/**
		*	@brief Returns the following vertex based on the specified index.
		*/
		Vertex next(int index);

		/**
		*	@brief Shows some information about the PolygonGeo.
		*/
		void out();

		/**
		*	@brief Returns the vertex previous to the one in the position index.
		*/
		Vertex previous(int index);

		/**
		*	@brief Assignment operator.
		*/
		Polygon& operator=(const Polygon& PolygonGeo);

		/**
		*	@brief Assuming that this is a convex Polygon, this method indicates if the point p is inside the Polygon.
		*/
		bool pointInConvexPolygon(Point& point);

		/**
		*	@brief Saves the coordinates of the PolygonGeo in file with the same format as the constructor.
		*/
		void save(const std::string& filename) const;

		/**
		*	@brief Modifies the vertex in a position.
		*/
		void set(Vertex& vertex, int pos);
	};
}



#endif /* PolygonGeo_H */

