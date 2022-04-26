/**
 * @file main.cpp
 *
 * @author algarcia|lidia
 *
 * @brief Función main y callbacks
 */

#define NOMINMAX

// ReSharper disable CppClangTidyClangDiagnosticImplicitFloatConversion
// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppTooWideScope
// ReSharper disable CppClangTidyClangDiagnosticImplicitFallthrough
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <chrono>
#include <thread>

#include "InclDraw2D.h"
#include "InclDraw3D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "Scene.h"
#include "DrawTests.h"
#include "DebugLogging.h"

using system_clock = std::chrono::system_clock;

std::chrono::time_point<system_clock> t0;
float deltaTime;
int min;
int sec;
int ms;


#define TIME(func,string)\
	t0 = system_clock::now();\
	(func);\
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - t0).count();\
	min = std::floor(deltaTime / 60000);\
	sec = std::floor(deltaTime / 1000 - min * 60);\
	ms = deltaTime - sec * 1000 - min * 60;\
	std::cout << "Tiempo en " << (string) << ": "\
	<< ((min == 0) ? "" : std::to_string(min) + ":") << std::to_string(sec) << ":" << std::to_string(ms) << std::endl

using namespace GEO;

Movements movimientoActivo = Movements::NONE;
bool botonPulsado = false;
double ratonX = 0;
double ratonY = 0;
int modeloActivo = -1;

DrawTests test2D;
DrawTests test3D;

void mostrarAyuda()
{
	std::cout << "Ayuda" << std::endl
		<< "================" << std::endl
		<< "Practica 2:" << std::endl
		<< "q -> Ejercicio 1: Nube de Puntos" << std::endl
		<< "w -> Ejercicio 2: Planos" << std::endl
		<< "e -> Ejercicio 3: Modelos de Triangulos" << std::endl
		<< std::endl
		<< "Practica 3:" << std::endl
		<< "r -> Ejercicio 1: Vaca con Nube de Puntos en su AABB + los de dentro son ROJOS" << std::endl
		<< "t -> Ejercicio 2: Plano formado por Puntos dentro de la vaca + Proyeccion de los Vertices de la Vaca" << std::endl
		<< std::endl
		<< "Practica 4:" << std::endl
		<< "y -> Voxel Model" << std::endl
		<< "u -> Point Into Mesh (tiempo TriangleModel vs VoxelModel)" << std::endl
		<< "i -> Point Into Mesh (puntos de menos en VoxelModel respecto a TriangleModel)" << std::endl
		<< std::endl
		<< "Practica 5:" << std::endl
		<< "K-MEANS Naive, Grid, PCL" << std::endl
		<< "o -> PointCloud 20 Clusters aleatorios" << std::endl
		<< "p -> PointCloud PCL Import Olivos y Ground" << std::endl
		<< "================" << std::endl
		<< "1 -> PLANTA" << std::endl
		<< "2 -> ALZADO" << std::endl
		<< "3 -> PERFIL" << std::endl
		<< "4 -> ISOMETRICO" << std::endl
		<< "Cursores y rueda ratón -> Rotación" << std::endl
		<< "================" << std::endl
		<< "h -> Muestra esta ayuda" << std::endl
		<< "Esc -> Cierra la aplicación" << std::endl;
}


void refreshWindow(GLFWwindow* ventana)
{
	try
	{
		Scene::getInstance()->refresh();
	}
	catch (std::runtime_error& e)
	{
		outputException(e, "refreshWindow");
	}

	glfwSwapBuffers(ventana);
}


void callbackTamFB(GLFWwindow* ventana, int ancho, int alto)
{
	if (ancho == 0 || alto == 0)
		return;
	Scene::getInstance()->changeTamViewport(ancho, alto);
}


// Implementado después de la función main
void callbackKey(GLFWwindow* window, int tecla, int scancode, int accion,
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
			refreshWindow(ventana);
			ultimaEjecucion = clock();
			movimientoActivo = Movements::NONE;
		}
}


void callbackMouseWheel(GLFWwindow* ventana, double incX, double incY)
{
	movimientoActivo = Movements::ZOOM;
	Scene::getInstance()->moveCamera(movimientoActivo, -incY);
	refreshWindow(ventana);
	movimientoActivo = Movements::NONE;
}


int main(int argc, char** argv)
{
	// SEED:
	std::srand(system_clock::now().time_since_epoch().count());

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

	GLFWwindow* miVentana = glfwCreateWindow(1024, 576, "Algoritmos Geometricos", nullptr, nullptr);

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

	glfwSetWindowRefreshCallback(miVentana, refreshWindow);
	glfwSetFramebufferSizeCallback(miVentana, callbackTamFB);
	glfwSetKeyCallback(miVentana, callbackKey);
	glfwSetMouseButtonCallback(miVentana, callbackMouseButton);
	glfwSetScrollCallback(miVentana, callbackMouseWheel);
	glfwSetCursorPosCallback(miVentana, callbackMouseMovevent);

	mostrarAyuda();

	try
	{
		Scene::getInstance()->setScene(1024, 576);
		Scene::getInstance()->setColorBack(0.1f,0.1f,0.1f,1.0f);


		while (!glfwWindowShouldClose(miVentana))
		{
			glfwPollEvents();
		}
	}
	catch (std::runtime_error& e)
	{
		outputException(e, "main(): renderLoop");
		glfwWindowShouldClose(miVentana);
	}

	std::cout << "End of application" << std::endl;
	glfwDestroyWindow(miVentana);
	miVentana = nullptr;
	glfwTerminate();
}

void resetScene()
{
	test2D.clear();
	test3D.clear();
}

static TriangleModel vaca("vaca");

static int k = 20;
static PointCloud3D::KmeansData kmeansNaiveData(k);
static PointCloud3D::KmeansData kmeansVoxelData(k);
static PointCloud3D::KmeansData kmeansPCLData(k);

void callbackKey(GLFWwindow* window, int tecla, int scancode, int accion,
				 int modificadores)
{
	GLfloat factor = 0;

	switch (tecla)
	{
	case GLFW_KEY_ESCAPE:
		if (accion == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		break;
	case GLFW_KEY_DELETE:
		if (accion == GLFW_PRESS)
		{
			resetScene();
			refreshWindow(window);
		}
		break;

		/*
		// ================================ POLIGONO ================================
	case GLFW_KEY_P:
		if (accion == GLFW_PRESS)
		{
			test2D.drawPolygon2D();

			refreshWindow(ventana);
		}
		break;
		
		// ================================ TRIANGULO ================================
	case GLFW_KEY_T:
		if (accion == GLFW_PRESS)
		{
			test2D.drawTriangle2D();

			refreshWindow(ventana);
		}
		break;

		// ================================ SEGMENTO / LINEA / RAYO ================================

	case GLFW_KEY_S:
		if (accion == GLFW_PRESS)
		{
			test2D.drawLines2D();

			refreshWindow(ventana);
		}
		break;

		// ================================ NUBE DE PUNTOS ================================
	case GLFW_KEY_C:
		if (accion == GLFW_PRESS)
		{
			test2D.drawPointCloud2D();

			refreshWindow(ventana);
		}
		break;
		
		// ================================ BEZIER ================================
	case GLFW_KEY_B:
		if (accion == GLFW_PRESS)
		{
			test2D.drawBezier2D();

			refreshWindow(ventana);
		}
		break;
		
		// ================================ INTERSECCIONES & DISTANCIAS ================================
	case GLFW_KEY_I:
		if (accion == GLFW_PRESS)
		{
			test2D.drawLineIntersections2D();

			refreshWindow(ventana);
		}
		break;

		*/
		
		// =============================== POINT CLOUDS y Puntos de mas distantes ===============================
	case GLFW_KEY_Q:
		if (accion == GLFW_PRESS)
		{
			test3D.drawMostDistancedPoints();
			
			refreshWindow(window);
		}
		break;

		// =============================== PLANOS y Intersecciones ===============================
	case GLFW_KEY_W:
		if (accion == GLFW_PRESS)
		{
			test3D.drawPlane();
			
			refreshWindow(window);
		}
		break;

		// =============================== MODELOS 3D y sus Triangulos mas alejados ===============================
	case GLFW_KEY_E:
		if (accion == GLFW_PRESS)
		{
			// Colorea los triangulos maximos y minimos en cada coordenada del modelo
			const TriangleModel vaca("vaca");
			test3D.drawModel(vaca);
			test3D.drawMaxMinTriangles(vaca);

			refreshWindow(window);
		}
		break;
		// =============================== MODELOS 3D y su AABB + Puntos dentro de la malla ===============================
	case GLFW_KEY_R:
		if (accion == GLFW_PRESS)
		{
			// Colorea los triangulos maximos y minimos en cada coordenada del modelo
			test3D.drawModel(vaca);

			test3D.drawAABB(vaca);
			
			PointCloud3D pc(50,  vaca.getAABB());

			std::vector<Vec3D> pointsInside = test3D.drawPointsInsideModel(pc, vaca, false);
			
			refreshWindow(window);
		}
		break;
		// =============================== MODELOS 3D y sus Triangulos mas alejados ===============================
	case GLFW_KEY_T:
		if (accion == GLFW_PRESS)
		{
			const TriangleModel model("cuenco");
			test3D.drawModel(model);
			test3D.drawMaxMinTriangles(model);

			// 50 puntos random dentro del AABB
			PointCloud3D pc(50, model.getAABB());

			// Puntos dentro del modelo
			std::vector<Vec3D> pointsInside;
			for (const Vec3D& point : pc.getPoints())
			{
				if (model.pointIntoMesh(point))
					pointsInside.push_back(point);

				// Maximo 3 puntos
				if (pointsInside.size() == 3)
					break;
			}
			
			if (pointsInside.size() < 3)
				std::cout << "No hay suficientes puntos dentro del modelo para crear un plano (" +
				std::to_string(pointsInside.size()) + " / 3) " << std::endl;
			else
			{
				// Con 3 puntos de dentro creamos un plano
				Plane projectionPlane = test3D.drawPlane(pointsInside[0], pointsInside[1], pointsInside[2]);

				test3D.drawPointCloudProjection(projectionPlane, model.getCloud());
			}
			refreshWindow(window);
		}
		break;

		// =============================== PRACTICA 4: VOXELIZACION ===============================
	case GLFW_KEY_Y:
		if (accion == GLFW_PRESS)
		{
			// Modelo Voxelizado:
			vaca.generateVoxelModel(.05f);
			
			test3D.drawVoxelModel(*vaca.getVoxelModel(), TypeVoxel::intersect);
			test3D.drawVoxelModel(*vaca.getVoxelModel(), TypeVoxel::in);
			
			refreshWindow(window);
		}
		break;
	case GLFW_KEY_U:
		if (accion == GLFW_PRESS)
		{
			// Calcula los puntos de una Nube de Puntos que caen dentro del modelo
			// Usando el TriangleModel y el VoxelModel y calcula cuanto tarda cada uno

			test3D.drawModel(vaca);

			// Generamos la nube de Puntos desde fichero
			int numPuntos = 1000;
			std::string pcFileName = std::to_string(numPuntos) + "PointsCuenco.txt";
			auto* pc = new PointCloud3D(pcFileName);

			// Si no esta el fichero guardado la generamos de 0 y lo guardamos
			if (pc->isEmpty())
			{
				pc = new PointCloud3D(numPuntos, vaca.getAABB());
				pc->save(pcFileName);
			}
			
			std::vector<Vec3D> pointsInsideA;
			std::vector<Vec3D> pointsInsideB;
			
			vaca.generateVoxelModel(.05);
			
			// Calculo del Tiempo de encontrar puntos dentro de una malla
			pointsInsideA = test3D.drawPointsInsideModel(*pc, vaca, false);

			// Calculo del Tiempo de encontrar puntos dentro de una malla con VOXELES
			pointsInsideB = test3D.drawPointsInsideModel(*pc, vaca, true);
			

			// Error acumulado del segundo metodo
			double sampleA = pointsInsideA.size();
			double sampleB = pointsInsideB.size();
			double error = (sampleB - sampleA) / std::max(sampleA, sampleB);

			std::cout << "Error en PointInMesh del VoxelModel: " << error * 100 << "%" << std::endl;

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_I:
		if (accion == GLFW_PRESS)
		{
			// Calcula el error que hay entre el metodo PointInMesh usando TriangleModel vs VoxelModel
			// Y dibuja los puntos que difieren entre ambos metodos

			test3D.drawModel(vaca);

			vaca.generateVoxelModel();

			// Generamos la nube de Puntos desde fichero
			int numPuntos = 1000;
			std::string pcFileName = std::to_string(numPuntos) + "PointsCuenco";
			auto* pc = new PointCloud3D(pcFileName);

			// Si no esta el fichero guardado la generamos de 0 y lo guardamos
			if (pc->isEmpty())
			{
				pc = new PointCloud3D(numPuntos, vaca.getAABB());
				pc->save(pcFileName);
			}

			test3D.drawPointsInsideModelDiff(*pc, vaca);
			
			
			refreshWindow(window);
		}
		break;
	case GLFW_KEY_O:
		if (accion == GLFW_PRESS)
		{
			double error = 0.001;
			
			static PointCloud3D pc(1000, k, 3, .4, .2);

			pc.generateVoxelGrid(.3);
			
			if (modificadores == GLFW_MOD_SHIFT)
			{
				test3D.kMeansAnimation(pc, k, error, window);
				break;
			}
						
			// NAIVE
			TIME( kmeansNaiveData = pc.kmeans_naive(k, error), "K-Means Naive");

			std::cout << "K-Means Naive completado. Iteraciones: " << kmeansNaiveData.iteration << std::endl;
			std::cout << std::endl;
			
			// Usando VOXELES
			TIME(kmeansVoxelData = pc.kmeans_grid(k, error), "K-Means Grid");
			
			std::cout << "K-Means Grid completado. Iteraciones: " << kmeansVoxelData.iteration << std::endl;
			std::cout << std::endl;

			// Usando PCL
			TIME(kmeansPCLData = pc.kmeans_pcl(k), "K-Means PCL");


			// Drawcalls
			for (int i = 0; i < k; ++i)
			{
				test3D.drawPointCloud3D(kmeansPCLData.clusters[i], colors[i % colors.size()]);
			}

			pc.save("clusters", true);

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_P:
		if (accion == GLFW_PRESS)
		{
			//PointCloud3D ground("ground.ply");
			PointCloud3D olivos("olivos.ply");
			Vec3D center = olivos.getAABB().getCenter();

			int numOlivos = 87;
			
			PointCloud3D::KmeansData olivosKmeansData(87);

			//// Naive
			//TIME(olivosKmeansData = olivos.kmeans_naive(numOlivos), "K-Means Naive para Olivos");
			//
			//std::cout << "K-Means Naive completado. Iteraciones: " << kmeansVoxelData.iteration << std::endl;
			//std::cout << std::endl;

			//// Grid
			//TIME(olivosKmeansData = olivos.kmeans_grid(numOlivos), "K-Means Grid para Olivos");
			//
			//std::cout << "K-Means Grid completado. Iteraciones: " << kmeansVoxelData.iteration << std::endl;
			//std::cout << std::endl;

			// PCL
			TIME(olivosKmeansData = olivos.kmeans_pcl_kdtree(numOlivos), "K-Means PCL para Olivos");

			for (int i = 0; i < olivosKmeansData.clusters.size(); ++i)
			{
				DrawCloud3D* dc = test3D.drawPointCloud3D(olivosKmeansData.clusters[i], colors[i % colors.size()]);
				dc->apply(glm::translate(glm::vec3(-center.getX(), -center.getY(), -center.getZ())));
				dc->apply(glm::scale(glm::vec3(.05, .05, .05)));
				dc->apply(glm::rotate(glm::pi<float>() / 4.5f, glm::vec3(0.f, 0.f, 1.f)));
			}

			//DrawCloud3D* dc = test3D.drawPointCloud3D(ground, grey);
			//dc->apply(glm::translate(glm::vec3(-center.getX(), -center.getY(), -center.getZ())));
			//dc->apply(glm::scale(glm::vec3(.05, .05, .05)));
			//dc->apply(glm::rotate(glm::pi<float>() / 4.5f, glm::vec3(0.f, 0.f, 1.f)));
			

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_A:
		if (accion == GLFW_PRESS)
		{

		}
		break;
	case GLFW_KEY_S:
		if (accion == GLFW_PRESS)
		{
			const PointCloud3D pc(100, 2, 3);

			test3D.drawPointCloud3D(pc, white);

			// K-MEANS

			refreshWindow(window);
		}
		break;

	case GLFW_KEY_V:
		if (accion == GLFW_PRESS)
		{
			test3D.drawModel(vaca);

			vaca.generateVoxelModel();

			test3D.drawVoxelModel(*vaca.getVoxelModel(), TypeVoxel::intersect);
			
			refreshWindow(window);
		}
		break;
	case GLFW_KEY_B:
		if (accion == GLFW_PRESS)
		{
			test3D.drawModel(vaca);

			vaca.generateVoxelModel();

			test3D.drawVoxelModel(*vaca.getVoxelModel(), TypeVoxel::intersect);
			test3D.drawVoxelModel(*vaca.getVoxelModel(), TypeVoxel::in);
			
			refreshWindow(window);
		}
		break;
	case GLFW_KEY_C:
		if (accion == GLFW_PRESS)
		{
			test3D.drawCuenco();
			
			refreshWindow(window);
		}
		break;


	case GLFW_KEY_1:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::PLANT);

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_2:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::ELEVATION);

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_3:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::PROFILE);

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_4:
		if (accion == GLFW_PRESS)
		{
			Scene::getInstance()->setView(TypeView::ISOMETRIC);

			refreshWindow(window);
		}
		break;
	case GLFW_KEY_H:
		if (accion == GLFW_PRESS)
		{
			mostrarAyuda();
		}
		break;

	case GLFW_KEY_LEFT:
		factor = -1;
	case GLFW_KEY_RIGHT:
		factor = (factor != -1) ? 1 : factor;
		if (accion == GLFW_PRESS)
		{
			switch (movimientoActivo)
			{
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, factor, 0);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, 10 * factor);
				break;
			case Movements::PAN:
				Scene::getInstance()->moveCamera(movimientoActivo, factor);
				break;
			case Movements::ZOOM:
			case Movements::CRANE:
			case Movements::TILT:
			case Movements::NONE: break;
			}
		}

		refreshWindow(window);
		break;
	case GLFW_KEY_UP:
		factor = 1;
	case GLFW_KEY_DOWN:
		factor = (factor != 1) ? -1 : factor;
		if (accion == GLFW_PRESS)
		{
			switch (movimientoActivo)
			{
			case Movements::TILT:
			case Movements::ZOOM:
				Scene::getInstance()->moveCamera(movimientoActivo, -factor);
				break;
			case Movements::CRANE:
				Scene::getInstance()->moveCamera(movimientoActivo, factor);
				break;
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, -factor);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, -10 * factor, 0);
				break;
			case Movements::NONE:
			case Movements::PAN:
				break;
			}
		}
		refreshWindow(window);
		break;
	default: ;
	}
}