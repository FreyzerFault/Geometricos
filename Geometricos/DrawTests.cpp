#include "DrawTests.h"

#include "DebugLogging.h"

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

void GEO::DrawTests::drawPointCloud2D()
{
	try
	{
		const PointCloud pc(50, 5, 5);
		drawIt<PointCloud, DrawPointCloud>(pc, red);

		pc.save("PointCloud");
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

		PointCloud pc;
		pc.addPoint(a);
		pc.addPoint(b);
		pc.addPoint(c);
		pc.addPoint(d);
		
		drawIt<PointCloud, DrawPointCloud>(pc, red);

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

void GEO::DrawTests::drawVaca()
{
	try
	{
		const TriangleModel vaca("obj/vaca.obj");
		drawIt<TriangleModel, DrawTriangleModel>(vaca, white);
		

		//Descomentar para ver como se pintan las 100 primeras caras del modelo de amarillo           


   //                std::cout << "hay un total de " << tm.numTriangulos() << " triángulos" << std::endl;
   //                TypeColor amarillo (1.0, 1.0, 0.0);  
   //                
   //                std::vector<Triangle3D> triangulos = tm.getFaces();
   //                Triangle3D tri; 
   //                DrawTriangle3d *dtri;  
   //                for (int i=0; i<100; i++){
   //                    tri = triangulos[i];
   //                    dtri = new DrawTriangle3d (tri);
   //                    dtri -> drawIt(amarillo);
   //                }

				   // descomentar para observar la nube de puntos asociada al modelo; 
				   //comentar antes la visualización completa del modelo

   //                PointCloud3d pc = tm.getCloud();
   //                DrawCloud3d *dpc = new DrawCloud3d (pc);
   //                dpc->drawIt();
   //                

				   // descomentar para observar los triángulos de forma individual. Es mucho más lento 
   //                TypeColor verde (0.0, 1.0, 0.0); 
   //                Triangle3D tri; 
   //                DrawTriangle3d *dtri;  
   //                for (unsigned i = 0; i<tm.numTriangulos()/2; i++){
   //                    tri = tm.getFace(i);
   //                    dtri = new DrawTriangle3d (tri);
   //                    dtri->drawIt(verde);
   //                }
   //                TypeColor magenta (1.0, 0.0, 1.0);  
   //                
   //                for (unsigned i = tm.numTriangulos()/2+1; i<tm.numTriangulos(); i++){
   //                    tri = tm.getFace(i);
   //                    dtri = new DrawTriangle3d (tri);
   //                    dtri->drawIt(magenta);
   //                }




	}
	catch (std::exception& e)
	{
		outputException(e, "drawVaca");
	}
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
}

void GEO::DrawTests::draw3DModel(const TriangleModel& model)
{
	drawPointers.push_back(new DrawTriangleModel(model));
	dynamic_cast<DrawTriangleModel*>(drawPointers[drawPointers.size() - 1])->drawItPlain();
}
