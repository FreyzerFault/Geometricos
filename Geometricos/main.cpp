/**
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


Movements movimientoActivo = Movements::NONE;
bool botonPulsado = false;
double ratonX = 0;
double ratonY = 0;
int modeloActivo = -1;


void mostrarAyuda ()
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


void refresWindow ( GLFWwindow* ventana )
{
   try
   {
      Scene::getInstance ()->refresh ();
   }
   catch ( std::runtime_error& e )
   {
      std::cout << "Exception on refeshWindow"
                << std::endl
                << "=============================================="
                << std::endl
                << e.what () << std::endl;
   }

   glfwSwapBuffers ( ventana );
}


void callbackTamFB ( GLFWwindow* ventana, int ancho, int alto )
{
   Scene::getInstance ()->changeTamViewport ( ancho, alto );
}


// Implementado después de la función main
void callbackKey ( GLFWwindow* ventana, int tecla, int scancode, int accion,
                     int modificadores );


void callbackMouseButton ( GLFWwindow* ventana, int boton, int accion,
                          int modificadores )
{
   if ( boton == 0 )
   {
      if ( accion == GLFW_PRESS )
      {
         botonPulsado = true;
         glfwGetCursorPos ( ventana, &ratonX, &ratonY );
      }

      if ( accion == GLFW_RELEASE )
      {
         botonPulsado = false;
         ratonX = 0;
         ratonY = 0;
      }
   }
}


void callbackMouseMovevent ( GLFWwindow* ventana, double posX, double posY )
{
   static clock_t ultimaEjecucion = clock ();   // Se inicializa una única vez

   movimientoActivo = Movements::ORBIT;
   
   if ( botonPulsado) 
       
      if ( ( clock () - ultimaEjecucion ) > 100 )
      {
         double incX = posX - ratonX;
         double incY = posY - ratonY;
         
         Scene::getInstance ()->moveCamera ( movimientoActivo,incY, incX );


         ratonX = posX;
         ratonY = posY;
         refresWindow ( ventana );
         ultimaEjecucion = clock ();
         movimientoActivo = Movements::NONE;
   }
}


void callbackMouseWheel ( GLFWwindow* ventana, double incX, double incY )
{
   
   movimientoActivo = Movements::ZOOM; 
   Scene::getInstance ()->moveCamera ( movimientoActivo, -incY); 
   refresWindow ( ventana );
   movimientoActivo = Movements::NONE;
    
    

}


int main ( int argc, char** argv )
{
   std::cout << "Prácticas de algoritmos Geométricos" << std::endl;

   if ( glfwInit ( ) != GLFW_TRUE )
   {
      std::cout << "Fallo al inicializar GLFW" << std::endl;
      return -1;
   }

   glfwWindowHint ( GLFW_SAMPLES, 4 );
   glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 );

   GLFWwindow *miVentana;
   miVentana = glfwCreateWindow ( 1024, 576, "Algoritmos Geométricos", nullptr, nullptr );

   if ( miVentana == nullptr )
   {
      std::cout << "Fail wheb initializing GLFW" << std::endl;
      glfwTerminate ( );
      return -2;
   }

   glfwMakeContextCurrent ( miVentana );

   glewExperimental = true;
   if ( glewInit ( ) != GLEW_OK )
   {
      std::cout << "Fail wheb initializing GLEW" << std::endl;
      glfwDestroyWindow ( miVentana );
      glfwTerminate ( );
      return -3;
   }

   std::cout << glGetString ( GL_RENDERER ) << std::endl
             << glGetString ( GL_VENDOR ) << std::endl
             << glGetString ( GL_VERSION ) << std::endl
             << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

   glfwSetWindowRefreshCallback ( miVentana, refresWindow );
   glfwSetFramebufferSizeCallback ( miVentana, callbackTamFB );
   glfwSetKeyCallback ( miVentana, callbackKey );
   glfwSetMouseButtonCallback ( miVentana, callbackMouseButton );
   glfwSetScrollCallback ( miVentana, callbackMouseWheel );
   glfwSetCursorPosCallback ( miVentana, callbackMouseMovevent );

   mostrarAyuda ();

   try
   {
      Scene::getInstance ()->setScene ( 1024, 576 );
      

      while ( !glfwWindowShouldClose ( miVentana ) )
      {
         glfwPollEvents ( );
      }
   }
   catch ( std::runtime_error& e )
   {
      std::cout << "Excepction captured: " << e.what () << std::endl;
      glfwWindowShouldClose ( miVentana );
   }

   std::cout << "End of application" << std::endl;
   glfwDestroyWindow ( miVentana );
   miVentana = nullptr;
   glfwTerminate ( );
}


void callbackKey ( GLFWwindow* ventana, int tecla, int scancode, int accion,
                     int modificadores )
{
   GLfloat f = 0;

   switch( tecla )
   {
      case GLFW_KEY_Q:
         if ( accion == GLFW_PRESS )
         {
            glfwSetWindowShouldClose ( ventana, GLFW_TRUE );
         }
         break;
         
        case GLFW_KEY_M:
         if ( accion == GLFW_PRESS )
         {  
            try
            {
               Vect2d a (3.0, 2.0);
               Vect2d b (0.0, 0.0);
               Vect2d c (-2.0, 1.0);
                
               Triangle t1 (a,b,c);
               DrawTriangle *dt1 = new DrawTriangle (t1);
               TypeColor magenta (1.0, 0.0, 1.0);
               dt1->drawIt(magenta);
               dt1 = nullptr;
            }
            catch ( std::exception& e )
            {
               std::cout << "Exception captured in callbackKey"
                         << std::endl
                         << "===================================="
                         << std::endl
                         << e.what () << std::endl;
            }

            refresWindow ( ventana );
         }
         break;         

         case GLFW_KEY_S:
         if ( accion == GLFW_PRESS )
         {  
            try
            {
               Vect2d a (2.0, 1.0);
               Vect2d b (0.0, 1.0);
               Vect2d c (-2.0, -2.0);
               Vect2d d (3.0, 0.0);
               
               
               //SegmentLine s1 (a,b);
               //DrawSegment *ds1 = new DrawSegment (s1);
               //ds1->drawIt(verde);
               //ds1 = nullptr;
               
//               PolygonGeo s2;
//               s2.add(a); s2.add(b); s2.add(c); s2.add(d);
//               DrawPolygonGeo *ds2 = new DrawPolygonGeo (s2);
//               TypeColor verde (0.0, 1.0, 0.0);
//               ds2->drawIt(verde);
//               ds2 = nullptr;
               
               PointCloud s3;
               s3.addPoint(a); s3.addPoint(b); s3.addPoint(c); s3.addPoint(d);
               DrawPointCloud *ds3 = new DrawPointCloud (s3);
               TypeColor verde (0.0, 0.0, 1.0);
               ds3 -> drawIt (verde);
               ds3 = nullptr;
               
               Vect2d s4 (0.0, 0.0);
               DrawPoint *ds4 = new DrawPoint (s4);
               TypeColor blue (0.0, 0.0, 1.0);
               ds4 -> drawIt (blue);
               ds4 = nullptr; 
               
            }
            catch ( std::exception& e )
            {
               std::cout << "Exception captured on callbackKey"
                         << std::endl
                         << "===================================="
                         << std::endl
                         << e.what () << std::endl;
            }

            refresWindow ( ventana );
         }
         break;  
         
         
         case GLFW_KEY_P:
         if ( accion == GLFW_PRESS )
         {  
            try
            {
               Point a (0.0, 0.0);
               DrawPoint *da = new DrawPoint (a);
               da->drawIt();
               da = nullptr;
            }
            catch ( std::exception& e )
            {
               std::cout << "Exception captured on callbackKey"
                         << std::endl
                         << "===================================="
                         << std::endl
                         << e.what () << std::endl;
            }

            refresWindow ( ventana );
         }
         break;  
         
         
      
       case GLFW_KEY_1:
         if ( accion == GLFW_PRESS )
         {
            Scene::getInstance ()->setView ( TypeView::PLANT );

            refresWindow ( ventana );
         }
         break;
      case GLFW_KEY_2:
         if ( accion == GLFW_PRESS )
         {
            Scene::getInstance ()->setView ( TypeView::ELEVATION );

            refresWindow ( ventana );
         }
         break;
      case GLFW_KEY_3:
         if ( accion == GLFW_PRESS )
         {
            Scene::getInstance ()->setView ( TypeView::PROFILE );

            refresWindow ( ventana );
         }
         break;
      case GLFW_KEY_4:
         if ( accion == GLFW_PRESS )
         {
            Scene::getInstance ()->setView ( TypeView::ISOMETRIC );

            refresWindow ( ventana );
         }
         break;
      case GLFW_KEY_H:
         if ( accion == GLFW_PRESS )
         {
            mostrarAyuda ();
         }
         break;

       case GLFW_KEY_LEFT:
         f = -1;
      case GLFW_KEY_RIGHT:
         f = ( f!=-1 ) ? 1 : f;
         if ( accion == GLFW_PRESS )
         {
            switch ( movimientoActivo )
            {
               case Movements::DOLLY:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, f, 0 );
                  break;
               case Movements::ORBIT:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, 0, 10*f );
                  break;
               case Movements::PAN:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, f );
                  break;
               case Movements::ZOOM:
               case Movements::CRANE:
               case Movements::TILT:
               default:
                  break;
            }
         }

         refresWindow ( ventana );
         break;
      case GLFW_KEY_UP:
         f = 1;
      case GLFW_KEY_DOWN:
         f = ( f!=1 ) ? -1 : f;
         if ( accion == GLFW_PRESS )
         {
            switch ( movimientoActivo )
            {
               case Movements::TILT:
               case Movements::ZOOM:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, -f );
                  break;
               case Movements::CRANE:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, f );
                  break;
               case Movements::DOLLY:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, 0, -f );
                  break;
               case Movements::ORBIT:
                  Scene::getInstance ()->moveCamera ( movimientoActivo, -10*f, 0 );
                  break;
               default:
                  break;
            }
         }
         refresWindow ( ventana );
         break;
         

   }

   std::cout << "The End" << std::endl;
}
