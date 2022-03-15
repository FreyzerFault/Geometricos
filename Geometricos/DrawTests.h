#pragma once

#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw2D.h"
#include "InclDraw3D.h"

namespace GEO
{
	class DrawTests
	{
		std::vector<Draw*> drawPointers;

	public:
		// 2D
		void drawPolygon2D();
		void drawTriangle2D();
		void drawLines2D();
		void drawPointCloud2D();
		void drawBezier2D();
		void drawLineIntersections2D();

		// 3D
		void drawPlane();

		void drawPointCloud3D();

		// Modelos 3D:
		void drawVaca();
		void drawCuenco();
		void drawDado();

		void drawModel(const TriangleModel& model);

		// AABB de un Modelo 3D
		void drawAABB(const TriangleModel& model);

		// Calcular los Triangulos del modelo con mayor y menor X, Y y Z
		void drawMaxMinTriangles(const TriangleModel& model);

		// Dibujar una nube de puntos dentro de un AABB
		PointCloud3D drawPointCloudInAABB(const AABB& aabb);

		std::vector<GEO::Vec3D> drawPointsInsideModel(const PointCloud3D& pc, const TriangleModel& model);

		void drawPlane(const Vec3D& a, const Vec3D& b, const Vec3D& c);

		void clear();

		template <typename T, typename D>
		void drawIt(const T& item, TypeColor color);

		template <typename T, typename D>
		void drawIt(const T& item, TypeColor color, TypeDraw typeDraw);

		void draw3DModel(const TriangleModel& model);
	};

	template <typename T, typename D>
	void DrawTests::drawIt(const T& item, TypeColor color)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt(color);
	}

	template <typename T, typename D>
	void DrawTests::drawIt(const T& item, TypeColor color, TypeDraw typeDraw)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt(color, typeDraw);
	}
}
