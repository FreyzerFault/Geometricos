
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
#include "Vertex.h"

namespace GEO
{
	class Polygon
	{
	protected:
		std::vector<Vertex> _vertices;
		
		// Comprueba si el vertice una vez añadido intersectaria su arista creada con cualquier segmento
		bool intersectsWithAnySegment(const Vertex& vertex) const;

	public:
		Polygon() = default;

		Polygon(std::vector<Vertex> vertices);

		// Importa el Poligono de un Archivo
		Polygon(const std::string& filename);
		
		Polygon(const Polygon& orig);
		
		Polygon& operator=(const Polygon& PolygonGeo);
		
		~Polygon() = default;
		
		// Añade un Vértice al final siempre que la arista creada no intersecte con las demás
		bool add(const Vertex& vertex);
		bool add(const Point& point);
		
		// Inserta un vertice en una posicion
		void set(Vertex& vertex, int pos);

		// Vertice en la posicion
		Vertex getVertexAt(int pos) const;
		SegmentLine getEdge(int pos) const; // Arista del Vertice
		
		// Siguiente vertice del que hay en index
		Vertex next(int index);
		Vertex previous(int index);

		int getNumVertices() const { return _vertices.size(); }

		
		// INTERSECCION con un segmento, linea o rayo
		Point* intersectionPoint(const SegmentLine& segment) const;
		Point* intersectionPoint(const RayLine& ray) const;
		Point* intersectionPoint(const Line& line) const;
		
		// Comprueba que todos sus vértices sean convexos
		bool convex() const;
		bool concave() const;
		
		// Si el Poligono es CONVEXO comprueba si point esta DENTRO del poligono
		bool pointInConvexPolygon(const Point& point) const;
		
		// Guarda el Poligono en un Archivo (Coordenadas de cada vertice en orden)
		void save(const std::string& filename) const;

		void out() const;
	};
}



#endif /* PolygonGeo_H */

