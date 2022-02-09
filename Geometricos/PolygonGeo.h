
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
#include "SegmentLine.h"
#include "Vect2d.h"
#include "Vertex.h"

    
class PolygonGeo
{
protected:
	std::vector<Vertex> _vertices;

protected:
	/**
	*	@brief Checks if a vertex (not included in the PolygonGeo) creates a segment with the last vertex that collides with any other segment.
	*/
	bool intersectsWithAnySegment(Vertex& vertex);

public:
	/**
	*	@brief Default empty constructor.
	*/
	PolygonGeo();

	/**
	*	@brief Constructor.
	*/
	PolygonGeo(std::vector<Vertex>& vertices);

	/**
	*	@brief Copy constructor.
	*/
	PolygonGeo(const PolygonGeo& PolygonGeo);

	/**
	*	@brief Constructor of a PolygonGeo from a file.
	*/
	PolygonGeo(const std::string& filename);

	/**
	*	@brief Destructor.
	*/
	~PolygonGeo();

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

	/**
	*	@brief Checks if a line intersects with the PolygonGeo.
	*	@param intersection If line and PolygonGeo intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	bool intersects(Line& line, Vect2d& interseccion);

	/**
	*	@brief Checks if a rayline intersects with the PolygonGeo.
	*	@param intersection If rayline and PolygonGeo intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	bool intersects(RayLine& ray, Vect2d& interseccion);

	/**
	*	@brief Checks if a segment intersects with the PolygonGeo.
	*	@param intersection If PolygonGeo and segment intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	bool intersects(SegmentLine& segment, Vect2d& interseccion);

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
	PolygonGeo& operator=(const PolygonGeo& PolygonGeo);

	/**
	*	@brief Assuming that this is a convex PolygonGeo, this method indicates if the point p is inside the PolygonGeo.
	*/
	bool pointInConvexPolygonGeo(Point& point);

	/**
	*	@brief Saves the coordinates of the PolygonGeo in file with the same format as the constructor.
	*/
	void save(const std::string& filename);

	/**
	*	@brief Modifies the vertex in a position.
	*/
	void set(Vertex& vertex, int pos);
};



#endif /* PolygonGeo_H */

