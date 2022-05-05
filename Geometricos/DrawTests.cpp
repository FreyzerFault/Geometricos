#include "DrawTests.h"

#include <chrono>
#include <thread>

#include "DebugLogging.h"

static float getDeltaTime(float t0)
{
	return (clock() - t0) / CLOCKS_PER_SEC;
}


void GEO::DrawTests::drawPolygon2D(){
	try
	{
		const Point a(0.0, 2.0);
		const Point b(2.0, 1.0);
		const Point c(2.0, -1.0);
		const Point d(0.0, -2.0);
		const Point e(-2.0, -1.0);
		const Point f(-2.0, 1.0);

		Polygon polygon;
		polygon.add(a);
		polygon.add(b);
		polygon.add(c);
		polygon.add(d);
		polygon.add(e);
		polygon.add(f);
		
		drawIt<Polygon, DrawPolygon>(polygon, cyan);

		polygon.save("Poligono1");
	}
	catch (std::exception& e)
	{
		outputException(e, "DrawPolygon2D");
	}
}

void GEO::DrawTests::drawTriangle2D()
{
	try
	{
		Vec2D a(3.0, 2.0);
		Vec2D b(0.0, 0.0);
		Vec2D c(-2.0, 1.0);

		const Triangle tri(a, b, c);
		drawIt<Triangle, DrawTriangle>(tri, magenta);
		
		// Posicion de a respecto a b y c
		std::cout << "Posicion de a respecto a (b,c):" << std::endl;
		std::cout << Point::classifyToString( a.classify(b,c) ) << std::endl;
	}
	catch (std::exception& e)
	{
		outputException(e, "drawTriangle2D");
	}
}

void GEO::DrawTests::drawLines2D()
{
	try
	{
		const Vec2D a(0.8, -1.3);
		const Vec2D b(1.0, 1.0);
		const Vec2D c(-0.8, -1.6);
		const Vec2D d(-1.3, -1.0);
		const Vec2D e(-1.0, 1.0);
		const Vec2D f(1.0, -1.0);

		const SegmentLine segment (a,b);
		drawIt<SegmentLine, DrawSegment>(segment, blue);

		const Line line (c,d);
		drawIt<Line, DrawLine>(line, red);

		const RayLine ray (e,f);
		drawIt<RayLine, DrawRay>(ray, yellow);
	}
	catch (std::exception& e)
	{
		outputException(e);
	}
}

void GEO::DrawTests::drawPointCloud2D(const PointCloud2D& pc, TypeColor color)
{
	try
	{
		drawIt<PointCloud2D, DrawCloud>(pc, color);

		pc.save("PointCloud2D");
	}
	catch (std::exception& e)
	{
		outputException(e, "drawPointCloud2D");
	}
}

void GEO::DrawTests::drawBezier2D()
{
	try
	{
		Point a(0.0, 2.0);
		Point b(2.0, 1.0);
		Point c(-2.0, -1.0);
		Point d(0.0, -2.0);

		PointCloud2D pc;
		pc.addPoint(a);
		pc.addPoint(b);
		pc.addPoint(c);
		pc.addPoint(d);
		
		drawIt<PointCloud2D, DrawCloud>(pc, red);

		Bezier bezier;
		bezier.addPoint(a);
		bezier.addPoint(b);
		bezier.addPoint(c);
		bezier.addPoint(d);
		
		drawIt<Bezier, DrawBezier>(bezier, yellow);

		bezier.save("Bezier");
	}
	catch (std::exception& e)
	{
		outputException(e, "drawBezier2D");
	}
}

void GEO::DrawTests::drawLineIntersections2D()
{
	try
	{
		const Point p(0.0, 0.0);
		const Point a(-1.0, 1.0);
		const Point b(1.0, -1.0);
		const Point c(-1.0, -1.0);
		const Point d(1.0, 1.0);

		const SegmentLine s(a,b);
		const Line l(a,d);
		const RayLine r(c,d);


		// INTERSECCIONES

		Point* segmLine = s.intersectionPoint(l);
		Point* segmRay = s.intersectionPoint(r);
		Point* lineRay = l.intersectionPoint(r);

		drawIt<SegmentLine, DrawSegment>(s, blue);
		drawIt<RayLine, DrawRay>(r, red);
		drawIt<Line, DrawLine>(l, green);

		if (segmLine)
			drawIt<Point, DrawPoint>(*segmLine, magenta);

		if (segmRay)
			drawIt<Point, DrawPoint>(*segmRay, magenta);

		if (lineRay)
			drawIt<Point, DrawPoint>(*lineRay, magenta);
		
		std::cout << std::endl;
		std::cout << "Interseccion entre Segmento (AZUL) y Line (VERDE): "
		<< (segmLine ? segmLine->toString() : "[No hay Interseccion]") << std::endl;
		std::cout << "Interseccion entre Segmento (AZUL) y Ray (ROJO): "
		<< (segmRay ? segmRay->toString() : "[No hay Interseccion]") << std::endl;
		std::cout << "Interseccion entre Line (VERDE) y Ray (ROJO): "
		<< (lineRay ? lineRay->toString() : "[No hay Interseccion]") << std::endl;

		// DISTANCIAS
		const double distS = s.distPoint(p);
		const double distL = l.distPoint(p);
		const double distR = r.distPoint(p);

		std::cout << "Distancia entre P y Segmento (AZUL): " << distS << std::endl;
		std::cout << "Distancia entre P y Recta (VERDE): " << distL << std::endl;
		std::cout << "Distancia entre P y Rayo (ROJO): " << distR << std::endl;
		
		drawIt<Point, DrawPoint>(p, white);

	}
	catch (std::exception& e)
	{
		outputException(e, "drawLineIntersections2D");
	}
}

void GEO::DrawTests::drawPlane()
{
	try
	{
		Vec3D a(0.0, 0.0, 0.0);
		Vec3D b(1.0, 0.0, 0.0);
		Vec3D c(1.0, 1.0, 1.0);

		Vec3D d(0.0, 0.0, 1.0);
		Vec3D e(1.0, 0.0, 0.0);
		Vec3D f(1.0, -1.0, 1.0);

		Vec3D g(0.0, 0.0, 0.0);
		Vec3D h(1.0, 1.0, 1.0);
		Vec3D i(1.0, 1.0, 0.0);

		/*Vec3D a(0.0, 0.0, 0.0);
		Vec3D b(1.0, 0.0, 0.0);
		Vec3D c(0.0, 0.0, 1.0);

		Vec3D d(-4.0, 0.0, 0.0);
		Vec3D e(0.0, 0.0, 3.0);
		Vec3D f(0.0, 4.0, 0.0);

		Vec3D g(0, -2, 0);
		Vec3D h(0, 0, -2);
		Vec3D i(1, 1, 0);*/

		//const Vec3D center(0,0,0);

		/*a = a + center;
		b = b + center;
		c = c + center;
		d = d + center;
		e = e + center;
		f = f + center;*/

		const Plane planeA(a,b,c);
		const Plane planeB(d,e,f);
		const Plane planeC(g,h,i);

		

		// INTERSECCIONES
		Line3D lAB, lBC, lAC;

		if (planeA.intersect(planeB, lAB))
			drawIt<Line3D, DrawLine3D>(lAB, red);

		if (planeB.intersect(planeC, lBC))
			drawIt<Line3D, DrawLine3D>(lBC, red);

		if (planeA.intersect(planeC, lAC))
			drawIt<Line3D, DrawLine3D>(lAC, red);

		Vec3D pABC;

		if (planeA.intersect(planeB, planeC, pABC))
			drawIt<Vec3D, DrawVec3D>(pABC, white);


		drawIt<Plane, DrawPlane>(planeA, yellow, TypeDraw::WIREFRAME);
		drawIt<Plane, DrawPlane>(planeB, cyan, TypeDraw::WIREFRAME);
		drawIt<Plane, DrawPlane>(planeC, magenta, TypeDraw::WIREFRAME);
		drawIt<Plane, DrawPlane>(planeA, yellow);
		drawIt<Plane, DrawPlane>(planeB, cyan);
		drawIt<Plane, DrawPlane>(planeC, magenta);
		
	}
	catch (std::exception& e)
	{
		outputException(e, "DrawPolygon2D");
	}
}

enum OrdenTriangulos
{
	MinX = 0,
	MinY = 1,
	MinZ = 2,
	MaxX = 3,
	MaxY = 4,
	MaxZ = 5,
};
std::string getOrden(int i)
{
	switch (i)
	{
	case 0:
		return "MinX";
	case 1:
		return "MinY";
	case 2:
		return "MinZ";
	case 3:
		return "MaxX";
	case 4:
		return "MaxY";
	case 5:
		return "MaxZ";

	default:
		return "MinX";
	}
}

GEO::DrawCloud3D* GEO::DrawTests::drawPointCloud3D(const PointCloud3D& pc, TypeColor color)
{
	try
	{
		glDisable(GL_BLEND);
		return drawIt<PointCloud3D, DrawCloud3D>(pc, color);
	}
	catch (std::exception& e)
	{
		outputException(e, "drawPointCloud3D");
	}
}

void GEO::DrawTests::drawVaca()
{
	try
	{
		const TriangleModel vaca("vaca");
		drawIt<TriangleModel, DrawTriangleModel>(vaca, white, TypeDraw::PLAIN);
		
		std::cout << "hay un total de " << vaca.numTriangulos() << " triángulos" << std::endl;

		// Triangulos de la Vaca:
		// La mitad son amarillos, la otra magentas
		/*for (unsigned i = 0; i < vaca.numTriangulos()/2; i++){
			Triangle3D tri(vaca.getFace(i));
			Vec3D normal = tri.getNormal() * 0.01;
			tri.setA(tri.getA() + normal);
			tri.setB(tri.getB() + normal);
			tri.setC(tri.getC() + normal);
			drawIt<Triangle3D, DrawTriangle3D>(tri, yellow);
		}
		
		for (unsigned i = vaca.numTriangulos()/2+1; i < vaca.numTriangulos(); i++){
			Triangle3D tri(vaca.getFace(i));
			Vec3D normal = tri.getNormal() * 0.01;
			tri.setA(tri.getA() + normal);
			tri.setB(tri.getB() + normal);
			tri.setC(tri.getC() + normal);
			drawIt<Triangle3D, DrawTriangle3D>(tri, magenta);
		}*/
	}
	catch (std::exception& e)
	{
		outputException(e, "drawVaca");
	}
}

void GEO::DrawTests::drawCuenco()
{
	try
	{
		const TriangleModel cuenco("cuenco");
		drawIt<TriangleModel, DrawTriangleModel>(cuenco, white);

		
	}
	catch (std::exception& e)
	{
		outputException(e, "drawCuenco");
	}
}

void GEO::DrawTests::drawDado()
{
	try
	{
		const TriangleModel dado("dado");
		drawIt<TriangleModel, DrawTriangleModel>(dado, white);
	}
	catch (std::exception& e)
	{
		outputException(e, "drawDado");
	}
}

void GEO::DrawTests::drawModel(const TriangleModel& model, TypeColor color)
{
	drawIt<TriangleModel, DrawTriangleModel>(model, color);
}

void GEO::DrawTests::drawMostDistancedPoints()
{
	try
	{
		const PointCloud3D pc(50, 1, 1, 1);
		drawPointCloud3D(pc, black);

		std::vector<Vec3D> points(6);
		pc.getMinPoints(points[MinX], points[MinY], points[MinZ]);
		pc.getMaxPoints(points[MaxX], points[MaxY], points[MaxZ]);

		int colorIndex = 0;
		for (int i = 0; i < points.size(); ++i)
		{
			const Vec3D& point = points[i];
			std::cout << getOrden(i) << ": " << point.toString() << std::endl;
			drawIt<Vec3D, DrawVec3D>(point, colors[colorIndex++]);
		}

		int a, b;
		pc.getMostDistanced(a, b);

		const Vec3D& maxPoint = pc.getPoint(a);
		const Vec3D& minPoint = pc.getPoint(b);

		maxPoint.out();
		minPoint.out();

		const Segment3D segment(minPoint, maxPoint);
		drawIt<Segment3D, DrawSegment3D>(segment, red);

		const Line3D line(minPoint, maxPoint);
		drawIt<Line3D, DrawLine3D>(line, yellow);

		Vec3D farPoint;
		double maxDistance = 0;
		const Edge3D* edge = &line;
		for (const Vec3D& point : pc.getPoints())
		{
			const double d = edge->distance(point);
			if (d > maxDistance)
			{
				farPoint = point;
				maxDistance = d;
			}
		}
		drawIt<Vec3D, DrawVec3D>(farPoint, cyan);

		const AABB aabb = pc.getAABB();
		drawIt<AABB, DrawAABB>(aabb, white);

		const Vec3D v1(1,0,0);
		const Vec3D v2(0,0,1);

		const Plane plane(aabb.getMin(), v1, v2, false);

		Line3D randomLine(pc.getRandomPoint(), pc.getRandomPoint());
		Vec3D intersectionPoint;
		while (!plane.intersect(randomLine, intersectionPoint))
		{
			randomLine = Line3D(pc.getRandomPoint(), pc.getRandomPoint());
		}

		drawIt<Line3D, DrawLine3D>(randomLine, red);
		drawIt<Vec3D, DrawVec3D>(intersectionPoint, white);
		
		drawIt<Plane, DrawPlane>(plane, yellow);
		
	}
	catch (std::exception& e)
	{
		outputException(e, "drawPointCloud3D");
	}
}

void GEO::DrawTests::drawAABB(const TriangleModel& model)
{
	const AABB aabb = model.getAABB();
	drawIt<AABB, DrawAABB>(aabb, white);
}

void GEO::DrawTests::drawMaxMinTriangles(const TriangleModel& model)
{
	try
	{
		// Sacamos los puntos limite de cada coordenada a partir de la nube de puntos
		const PointCloud3D cloud = model.getCloud();

		std::vector<Vec3D> points(6);
		cloud.getMinPoints(points[MinX], points[MinY], points[MinZ]);
		cloud.getMaxPoints(points[MaxX], points[MaxY], points[MaxZ]);
		
		// Listas con los Triangulos que interesan
		std::vector<std::vector<Triangle3D>> tris(6);

		for (unsigned i = 0; i < model.numTriangulos(); i++)
		{
			Triangle3D tri(model.getFace(i));
			Vec3D a = tri.getA();
			Vec3D b = tri.getB();
			Vec3D c = tri.getC();

			// Busca los Triangulos que tengan un punto que coincida
			if (a == points[MaxX] || b == points[MaxX] || c == points[MaxX])
				tris[MaxX].push_back(tri);

			if (a == points[MaxY] || b == points[MaxY] || c == points[MaxY])
				tris[MaxY].push_back(tri);

			if (a == points[MaxZ] || b == points[MaxZ] || c == points[MaxZ])
				tris[MaxZ].push_back(tri);

			if (a == points[MinX] || b == points[MinX] || c == points[MinX])
				tris[MinX].push_back(tri);

			if (a == points[MinY] || b == points[MinY] || c == points[MinY])
				tris[MinY].push_back(tri);

			if (a == points[MinZ] || b == points[MinZ] || c == points[MinZ])
				tris[MinZ].push_back(tri);
		}
		// Dibujamos todos los triangulos de cada lista de un color distinto
		int colorIndex = 0;
		for (auto& list : tris)
		{
			const TypeColor color = colors[colorIndex++];
			for (Triangle3D& tri : list)
			{
				// Antes de dibujarlos los movemos hacia fuera un poco para que si se renderiza a la vez del modelo no se superponga
				Vec3D normal = tri.getNormal() * 0.01;
				tri.setA(tri.getA() + normal);
				tri.setB(tri.getB() + normal);
				tri.setC(tri.getC() + normal);
				drawIt<Triangle3D, DrawTriangle3D>(tri, color);
			}
		}
	}
	catch (std::exception& e)
	{
		outputException(e, "drawMaxMinTriangles");
	}
}

GEO::PointCloud3D GEO::DrawTests::drawPointCloudInAABB(const AABB& aabb)
{
	PointCloud3D pc(50, aabb.getMax().getX(), aabb.getMax().getY(), aabb.getMax().getZ());
	drawIt<PointCloud3D, DrawCloud3D>(pc, white);

	return pc;
}

std::vector<GEO::Vec3D> GEO::DrawTests::drawPointsInsideModel(const PointCloud3D& pc, const TriangleModel& model, const bool useVoxel)
{
	const clock_t time = clock();
	std::vector<Vec3D> pointsInside = model.pointCloudIntoMesh(pc, useVoxel);
	std::cout << "Tiempo de PointInMesh (usando " << (useVoxel ? "VoxelModel" : "TriangleModel") << "): "
	+ std::to_string(getDeltaTime(time)) << " seconds" << std::endl;

	for (const Vec3D& point : pc.getPoints())
	{
		TypeColor color = white;

		// Si esta dentro lo dibujamos de rojo
		for (Vec3D& inside : pointsInside)
		{
			if (inside == point)
				color = red;
		}
		
		drawIt<Vec3D, DrawVec3D>(point, color);
	}
	
	return pointsInside;
}

std::vector<GEO::Vec3D> GEO::DrawTests::drawPointsInsideModelDiff(const PointCloud3D& pc, const TriangleModel& model)
{
	std::vector<Vec3D> pointsInside = model.pointCloudIntoMesh(pc, false);
	std::vector<Vec3D> pointsInsideByVoxel = model.pointCloudIntoMesh(pc, true);

	// Error acumulado del segundo metodo
	const double sampleA = pointsInside.size();
	const double sampleB = pointsInsideByVoxel.size();
	const double error = (sampleB - sampleA) / std::max(sampleA, sampleB);

	std::cout << "Error en PointInMesh del VoxelModel: " << error * 100 << "%"
	<< " (TriModel: " << sampleA << " vs VoxelModel: " << sampleB << ")" << std::endl;

	// Dibujamos solo los puntos que difieren
	for (const Vec3D& point : pointsInside)
	{
		bool diff = true;

		// Si encontramos que el metodo de Voxel tambien lo ha clasificado como dentro, no se dibuja
		for (Vec3D& pointByVoxel : pointsInsideByVoxel)
		{
			if (pointByVoxel == point)
			{
				diff = false;
			}
		}

		// Lo dibujamos si difiere
		if (diff)
			drawIt<Vec3D, DrawVec3D>(point, white);
	}
	
	return pointsInside;
}

GEO::Plane GEO::DrawTests::drawPlane(const Vec3D& a, const Vec3D& b, const Vec3D& c)
{
	const Plane p(a,b,c);
	drawIt<Plane, DrawPlane>(p, yellow, TypeDraw::TRANSPARENCY);

	return p;
}

GEO::PointCloud3D GEO::DrawTests::drawPointCloudProjection(const Plane& plane, const PointCloud3D& cloud)
{
	PointCloud3D projectedPC = plane.projectedCloud(cloud);
	drawIt<PointCloud3D, DrawCloud3D>(projectedPC, red);

	return projectedPC;
}

void GEO::DrawTests::clear()
{
	for (const Draw* drawPtr : drawPointers)
	{
		// Busca en la escena el modelo y lo elimina
		for (int i = 0; i < Scene::getInstance()->getNumModels(); ++i)
		{
			if (Scene::getInstance()->getModel(i) == drawPtr)
				Scene::getInstance()->deleteModel(i);
		}
	}
	drawPointers.clear();
	drawVoxelModels.clear();
}

void GEO::DrawTests::reloadWindow(GLFWwindow* window)
{	
	try
	{
		Scene::getInstance()->refresh();
	}
	catch (std::runtime_error& e)
	{
		outputException(e, "refreshWindow");
	}

	glfwSwapBuffers(window);
}

void GEO::DrawTests::draw3DModel(const TriangleModel& model)
{
	drawPointers.push_back(new DrawTriangleModel(model));
	dynamic_cast<DrawTriangleModel*>(drawPointers[drawPointers.size() - 1])->drawIt(TypeDraw::PLAIN);
}

void GEO::DrawTests::drawVoxel(const Voxel& voxel, TypeColor color)
{
	drawIt<Voxel, DrawVoxel>(voxel, color);
}

void GEO::DrawTests::drawVoxelModel(const VoxelModel& voxelModel, TypeVoxel type)
{
	drawVoxelModels.emplace_back(voxelModel);

	drawPointers.push_back(drawVoxelModels.back().drawIt(type));
}

void GEO::DrawTests::drawVoxelGrid(const VoxelGrid& grid, TypeColor color)
{
	drawIt<VoxelGrid, DrawVoxelGrid>(grid, color);
}

void GEO::DrawTests::kMeansAnimation(const PointCloud3D& pc, int k, double error, GLFWwindow* window, PointCloud3D::TypeKmeans type)
{
	if (type != PointCloud3D::naive && type != PointCloud3D::grid)
	{
		std::cout << "Animacion no implementada" << std::endl;
		return;
	}

	static PointCloud3D::KmeansData kmeansData(k);

	glDisable(GL_BLEND);

	if (kmeansData.iteration == 0)
	{
		kmeansData = pc.kmeans_progressive(k, kmeansData, type);

		clear();
		for (int i = 0; i < k; ++i)
		{
			drawPointCloud3D(kmeansData.clusters[i], colors[i % colors.size()]);
		}
		
		reloadWindow(window);
	}
	else
	{
		while (kmeansData.differentCentroids(error))
		{
			kmeansData = pc.kmeans_progressive(k, kmeansData, type);
			
			clear();
			for (int i = 0; i < k; ++i)
			{
				drawPointCloud3D(kmeansData.clusters[i], colors[i % colors.size()]);
			}

			constexpr int orbitCount = 2;
			for (int i = 0; i < orbitCount; ++i)
			{
				Scene::getInstance()->moveCamera(Movements::ORBIT, 0, 2);
				std::this_thread::sleep_for(std::chrono::milliseconds(30));

				reloadWindow(window);
			}
		}
		
		std::cout << "K-Means "
		<< (type == PointCloud3D::TypeKmeans::naive ? "Naive" : "Grid")
		<< " completado. Iteraciones: " << kmeansData.iteration << std::endl;
		std::cout << std::endl;

		// Reset kmeans
		kmeansData.iteration = 0;
	}
}

void GEO::DrawTests::drawTDelaunay(const TDelaunay& delaunay, TypeColor triColor, TypeColor lineColor)
{
	const DrawTDelaunay draw(delaunay);
	const std::pair<Draw*, Draw*> draws = draw.drawIt(triColor, lineColor);
	drawPointers.push_back(draws.first);
	drawPointers.push_back(draws.second);
}

void GEO::DrawTests::drawConvexHull(const ConvexHull3D& convexHull, TypeColor triColor, TypeColor lineColor)
{
	const DrawConvexHull3D draw(convexHull);
	const std::pair<Draw*, Draw*> draws = draw.drawIt(triColor, lineColor);
	drawPointers.push_back(draws.first);
	drawPointers.push_back(draws.second);
}
