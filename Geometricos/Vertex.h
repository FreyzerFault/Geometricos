/* 
 * File:   Vertex.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 10:22
 */
#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "Point.h"
#include "SegmentLine.h"

namespace GEO
{
	class Polygon;			// Forward declaration due to circular reference betwen both classes.

	class   Vertex : public Point
	{
	protected:
		constexpr static int INVALID_POSITION = -1;
		
		Polygon* _polygon;							// Polygon where the vertex belongs to.
		int _position;										// Position of the vertex in the polygon.

	public:
		// Vertex sin Poligono, Position = -1
		Vertex();
		Vertex(const Point& point);

		Vertex(const Point& point, Polygon* polygon, int pos = -1);

		Vertex(const Vertex& orig) = default;
		
		Vertex& operator=(const Vertex& vertex);
		
		~Vertex() override = default;

		// Concavo o Convexo respecto al Poligono
		bool concave() const;
		bool convex() const;
		

		// Siguiente Vértice
		Vertex next() const; // Counterclockwise
		Vertex previous() const; // Clockwise

		// Siguiente Arista
		SegmentLine nextEdge() const; // Counterclockwise
		SegmentLine previousEdge() const; // Clockwise


		Point getPoint() const { return {_x, _y}; }
		Polygon* getPolygon() const { return _polygon; }
		int getPositionInPolygon() const { return _position; }

		void setPoint(const Point& point) { _x = point.getX(); _y = point.getY(); }
		void setPolygon(Polygon* polygon) { _polygon = polygon; }
		void setPosition(const int pos) { _position = pos; }

		void out() const override;
	};
}




#endif /* VERTEX_H */

