﻿/**
 * @file main.cpp
 *
 * @author algarcia|lidia
 *
 * @brief Función main y callbacks
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/transform.hpp>
#include "Scene.h"

#include "InclGeom2D.h"
#include "InclDraw2D.h"
#include "RayLine.h"

using namespace GEO;


// Colores
const TypeColor magenta(1.0, 0.0, 1.0);
const TypeColor green(0.0, 1.0, 0.0);
const TypeColor blue(0.0, 0.0, 1.0);
const TypeColor red(1.0, 0.0, 0.0);
const TypeColor cyan(0.0, 1.0, 1.0);
const TypeColor yellow(1.0, 1.0, 0.0);



Movements movimientoActivo = Movements::NONE;
bool botonPulsado = false;
double ratonX = 0;
double ratonY = 0;
int modeloActivo = -1;


void mostrarAyuda()
{
	std::cout << "Ayuda" << std::endl
		<< "================" << std::endl
		<< "m -> Añade mi triángulo a la escena" << std::endl
		<< "p -> Añade un punto a la escena" << std::endl
		<< "s -> Añade una nube de puntos a la escena" << std::endl
		<< "Cursores y rueda ratón -> Rotación" << std::endl
		<< "h -> Muestra esta ayuda" << std::endl
		<< "q -> Cierra la aplicación" << std::endl;
}


void refresWindow(GLFWwindow* ventana)
{
	try
	{
		Scene::getInstance()->refresh();
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception on refeshWindow"
			<< std::endl
			<< "=============================================="
			<< std::endl
			<< e.what() << std::endl;
	}

	glfwSwapBuffers(ventana);
}


void callbackTamFB(GLFWwindow* ventana, int ancho, int alto)
{
	Scene::getInstance()->changeTamViewport(ancho, alto);
}


// Implementado después de la función main
void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
				 int modificadores);


void callbackMouseButton(GLFWwindow* ventana, int boton, int accion,
						 int modificadores)
{
	if (boton == 0)
	{
		if (accion == GLFW_PRESS)
		{
			botonPulsado = true;
			glfwGetCursorPos(ventana, &ratonX, &ratonY);
		}

		if (accion == GLFW_RELEASE)
		{
			botonPulsado = false;
			ratonX = 0;
			ratonY = 0;
		}
	}
}


void callbackMouseMovevent(GLFWwindow* ventana, double posX, double posY)
{
	static clock_t ultimaEjecucion = clock(); // Se inicializa una única vez

	movimientoActivo = Movements::ORBIT;

	if (botonPulsado)

		if ((clock() - ultimaEjecucion) > 10)
		{
			const double incX = posX - ratonX;
			const double incY = posY - ratonY;

			Scene::getInstance()->moveCamera(movimientoActivo, incY, incX);


			ratonX = posX;
			ratonY = posY;
			refresWindow(ventana);
			ultimaEjecucion = clock();
			movimientoActivo = Movements::NONE;
		}
}


void callbackMouseWheel(GLFWwindow* ventana, double incX, double incY)
{
	movimientoActivo = Movements::ZOOM;
	Scene::getInstance()->moveCamera(movimientoActivo, -incY);
	refresWindow(ventana);
	movimientoActivo = Movements::NONE;
}


int main(int argc, char** argv)
{
	// Para que salga por consola los caracteres especiales (ñ)
	setlocale(LC_ALL, "spanish");

	std::cout << "Prácticas de algoritmos Geométricos" << std::endl;

	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "Fallo al inicializar GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* miVentana;
	miVentana = glfwCreateWindow(1024, 576, "Algoritmos Geometricos", nullptr, nullptr);

	if (miVentana == nullptr)
	{
		std::cout << "Fail wheb initializing GLFW" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(miVentana);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Fail wheb initializing GLEW" << std::endl;
		glfwDestroyWindow(miVentana);
		glfwTerminate();
		return -3;
	}

	std::cout << glGetString(GL_RENDERER) << std::endl
		<< glGetString(GL_VENDOR) << std::endl
		<< glGetString(GL_VERSION) << std::endl
		<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSetWindowRefreshCallback(miVentana, refresWindow);
	glfwSetFramebufferSizeCallback(miVentana, callbackTamFB);
	glfwSetKeyCallback(miVentana, callbackKey);
	glfwSetMouseButtonCallback(miVentana, callbackMouseButton);
	glfwSetScrollCallback(miVentana, callbackMouseWheel);
	glfwSetCursorPosCallback(miVentana, callbackMouseMovevent);

	mostrarAyuda();

	try
	{
		Scene::getInstance()->setScene(1024, 576);


		while (!glfwWindowShouldClose(miVentana))
		{
			glfwPollEvents();
		}
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Excepction captured: " << e.what() << std::endl;
		glfwWindowShouldClose(miVentana);
	}

	std::cout << "End of application" << std::endl;
	glfwDestroyWindow(miVentana);
	miVentana = nullptr;
	glfwTerminate();
}


void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
				 int modificadores)
{
	GLfloat f = 0;

	switch (tecla)
	{
	case GLFW_KEY_Q:
		if (accion == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(ventana, GLFW_TRUE);
		}
		break;

	case GLFW_KEY_E:
		if (accion == GLFW_PRESS)
		{
			try
			{
				Vec2D a(3.0, 2.0);
				Vec2D b(0.0, 0.0);
				Vec2D c(-2.0, 1.0);

			}
			catch (std::exception& e)
			{
				std::cout << "Exception captured in callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_M:
		if (accion == GLFW_PRESS)
		{
			try
			{
				Vec2D a(3.0, 2.0);
				Vec2D b(0.0, 0.0);
				Vec2D c(-2.0, 1.0);

				Triangle t1(a, b, c);
				auto dt1 = new DrawTriangle(t1);
				dt1->drawIt(magenta);
				dt1 = nullptr;

				// Posicion de a respecto a b y c
				std::cout << "Posicion de a respecto a (b,c):" << std::endl;
				std::cout << Point::classifyToString( a.classify(b,c) ) << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << "Exception captured in callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;

	case GLFW_KEY_S:
		if (accion == GLFW_PRESS)
		{
			try
			{
				Vec2D a(2.0, 1.0);
				Vec2D b(0.0, 1.0);
				Vec2D c(-2.0, -2.0);
				Vec2D d(3.0, 0.0);

				SegmentLine s1 (a,b);
				DrawSegment *ds1 = new DrawSegment (s1);
				ds1->drawIt(blue);
				ds1 = nullptr;

				Line line (a,b);
				DrawLine *dl = new DrawLine (line);
				dl->drawIt(yellow);
				dl = nullptr;

				GEO::RayLine ray (a,b);
				DrawRay *dr = new DrawRay (ray);
				dr->drawIt(cyan);
				dr = nullptr;

				GEO::Polygon s2;
				s2.add(a); s2.add(b); s2.add(c); s2.add(d);
				DrawPolygon *ds2 = new DrawPolygon (s2);
				ds2->drawIt(green);
				ds2 = nullptr;

				s2.save("Poligono1");

				PointCloud s3;
				s3.addPoint(a);
				s3.addPoint(b);
				s3.addPoint(c);
				s3.addPoint(d);
				auto ds3 = new DrawPointCloud(s3);
				ds3->drawIt(green);
				ds3 = nullptr;

				Vec2D s4(0.0, 0.0);
				auto ds4 = new DrawPoint(s4);
				ds4->drawIt(blue);
				ds4 = nullptr;
			}
			catch (std::exception& e)
			{
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;


	case GLFW_KEY_P:
		if (accion == GLFW_PRESS)
		{
			try
			{
				Point a(0.0, 0.0);
				auto da = new DrawPoint(a);
				da->drawIt();
				da = nullptr;
			}
			catch (std::exception& e)
			{
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refresWindow(ventana);
		}
		break;


	case GLFW_KEY_1:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::PLANT);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_2:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::ELEVATION);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_3:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::PROFILE);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_4:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::ISOMETRIC);

			refresWindow(ventana);
		}
		break;
	case GLFW_KEY_H:
		if (accion == GLFW_PRESS)
		{
			mostrarAyuda();
		}
		break;

	case GLFW_KEY_LEFT:
		f = -1;
	case GLFW_KEY_RIGHT:
		f = (f != -1) ? 1 : f;
		if (accion == GLFW_PRESS)
		{
			switch (movimientoActivo)
			{
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, f, 0);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, 10 * f);
				break;
			case Movements::PAN:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::ZOOM:
			case Movements::CRANE:
			case Movements::TILT:
			default:
				break;
			}
		}

		refresWindow(ventana);
		break;
	case GLFW_KEY_UP:
		f = 1;
	case GLFW_KEY_DOWN:
		f = (f != 1) ? -1 : f;
		if (accion == GLFW_PRESS)
		{
			switch (movimientoActivo)
			{
			case Movements::TILT:
			case Movements::ZOOM:
				Scene::getInstance()->moveCamera(movimientoActivo, -f);
				break;
			case Movements::CRANE:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, -f);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, -10 * f, 0);
				break;
			default:
				break;
			}
		}
		refresWindow(ventana);
		break;
	}
}
