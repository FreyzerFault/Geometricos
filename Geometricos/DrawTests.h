#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw2D.h"
#include "InclDraw3D.h"

namespace GEO
{
	class DrawTests
	{
		std::vector<Draw*> drawPointers;
		std::vector<DrawVoxelModel> drawVoxelModels;

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
		DrawCloud3D* drawPointCloud3D(const PointCloud3D& pc, TypeColor color);

		// Modelos 3D:
		void drawVaca();
		void drawCuenco();
		void drawDado();

		void drawModel(const TriangleModel& model);

		// Ejercicios
		// Puntos mas distanciados en una nube
		void drawMostDistancedPoints();

		// AABB de un Modelo 3D
		void drawAABB(const TriangleModel& model);

		// Calcular los Triangulos del modelo con mayor y menor X, Y y Z
		void drawMaxMinTriangles(const TriangleModel& model);

		// Dibujar una nube de puntos dentro de un AABB
		PointCloud3D drawPointCloudInAABB(const AABB& aabb);

		// Dibujar nube de puntos, los puntos dentro del modelo son ROJOS
		std::vector<Vec3D> drawPointsInsideModel(const PointCloud3D& pc, const TriangleModel& model, const bool useVoxel);

		// Dibuja solo los puntos de la Nube de Puntos que estan dentro del modelo pero solo los que no considera el metodo con voxeles
		std::vector<Vec3D> drawPointsInsideModelDiff(const PointCloud3D& pc, const TriangleModel& model);

		// Dibujar un plano a partir de 3 puntos
		Plane drawPlane(const Vec3D& a, const Vec3D& b, const Vec3D& c);

		// Dibujar una nube de puntos proyectada en un plano
		PointCloud3D drawPointCloudProjection(const Plane& plane, const PointCloud3D& cloud);

		void clear();

		void reloadWindow(GLFWwindow* window);

		template <class T, class D>
		D* drawIt(const T& item);

		template <typename T, typename D>
		D* drawIt(const T& item, TypeColor color);

		template <typename T, typename D>
		D* drawIt(const T& item, TypeColor color, TypeDraw typeDraw);

		void draw3DModel(const TriangleModel& model);

		void drawVoxel(const Voxel& voxel, TypeColor color);
		void drawVoxelModel(const VoxelModel& voxelModel, TypeVoxel type = TypeVoxel::intersect);
		void drawVoxelGrid(const VoxelGrid& grid, TypeColor color);

		void kMeansAnimation(PointCloud3D& pc, int k, double error, GLFWwindow* window);
	};

	template <typename T, typename D>
	D* DrawTests::drawIt(const T& item)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt();
		return dynamic_cast<D*>(drawPointers[drawPointers.size() - 1]);
	}

	template <typename T, typename D>
	D* DrawTests::drawIt(const T& item, TypeColor color)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt(color);
		return dynamic_cast<D*>(drawPointers[drawPointers.size() - 1]);
	}

	template <typename T, typename D>
	D* DrawTests::drawIt(const T& item, TypeColor color, TypeDraw typeDraw)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt(color, typeDraw);
		return dynamic_cast<D*>(drawPointers[drawPointers.size() - 1]);
	}
}
