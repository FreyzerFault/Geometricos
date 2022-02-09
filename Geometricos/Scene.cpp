/**
 * @file PAGrenderer.cpp
 * @author algarcia
 *
 * @date 28 de septiembre de 2020, 12:19
 *
 * @brief Implementación de los métodos de la clase PAGrenderer
 */

#include <string>
#include <stdexcept>
#include "Scene.h"


Scene* Scene::_instance = nullptr;

/**
 * Destructor.
 * Elimina los modelos, si los hubiera
 */
Scene::~Scene ( )
{
   if ( ! _models.empty () )
   {
      for ( Draw* m : _models )
      {
         if ( m != nullptr )
         {
            delete m;
            m = nullptr;
         }
      }
   }
}


void Scene::setScene (GLint anchoViewport, GLint altoViewport){
      initScene ( anchoViewport, altoViewport);
      Light l;
      l.setType ( TypeLight::AMBIENT )
       .setIa ( glm::vec3 ( .2, .2, .2 ) );
      Scene::getInstance ()->addLight ( l );
      l.setType ( TypeLight::PUNCTUAL )
       .setId ( glm::vec3 ( 1, 1, 1 ) )
       .setIs ( glm::vec3 ( 1, 1, 1 ) )
       .setPosition ( glm::vec3 ( -1.5, .25, .25 ) );
      Scene::getInstance ()->addLight ( l );
      l.setType ( TypeLight::DIRECTIONAL )
       .setId ( glm::vec3 ( 1, 1, 1 ) )
       .setIs ( glm::vec3 ( 1, 1, 1 ) )
       .setDirection ( glm::vec3 ( 0, 1, 1 ) );
      Scene::getInstance ()->addLight ( l );
      l.setType ( TypeLight::SPOT )
       .setId ( glm::vec3 ( 1, 1, 1 ) )
       .setIs ( glm::vec3 ( 1, 1, 1 ) )
       .setPosition ( glm::vec3 ( 1.5, 1.5, 1.5 ) )
       .setDirection ( glm::vec3 ( -1, -1, -1 ) );
      Scene::getInstance ()->addLight ( l );
      Scene::getInstance ()->setView ( TypeView::ELEVATION );

    
}

/**
 * Método para consultar la instancia única de la clase
 * @return Un puntero a la instancia única de la clase
 * @throw std::runtime_error Si hay algún error
 */
Scene* Scene::getInstance ( )
{
   if ( !_instance )
   {
      try
      {
         _instance = new Scene;
      }
      catch ( std::runtime_error& e )
      {
         std::string mensaje = "Scene::getInstancia ->\n";
         throw std::runtime_error ( mensaje + e.what () );
      }
   }

   return _instance;
}


/**
 * Método para hacer el refresco de la escena
 * @throw std::runtime_error Si hay algún error
 */
void Scene::refresh ( )
{
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

   if ( !_models.empty () )
   {
      glm::mat4 mV = _camera.getMvis ();
      glm::mat4 mVP = _camera.getMvp ();

      try
      {
         glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
         for ( Draw* m : _models )
         {
            if ( m != nullptr )
            {
               m->render ( mV, mVP, _lights[0] );
            }
         }

         glBlendFunc ( GL_SRC_ALPHA, GL_ONE );
         for ( int i = 1; i < _lights.size (); i++ )
         {
            for ( Draw* m : _models )
            {
               if ( m != nullptr )
               {
                  m->render( mV, mVP, _lights[i] );
               }
            }
         }
      }
      catch ( std::runtime_error& e )
      {
         std::string mensaje = "Scene::refrescar -> ";
         throw std::runtime_error ( mensaje + e.what () );
      }
   }
}


/**
 * Método para cambiar el tamaño del viewport
 * @param ancho Ancho del nuevo viewport
 * @param alto Alto del nuevo viewport
 * @pre Tanto alto como ancho deben ser valores positivos
 */
void Scene::changeTamViewport ( GLint ancho, GLint alto )
{
   _camera.setViewport ( ancho, alto );
   glViewport ( 0, 0, ancho, alto );
}


/**
 * Método para consultar el color de fondo de la escena
 * @param valores Dirección de memoria de un bloque de cuatro valores a los que
 *                se le copiarán las componentes del color (R, G, B, A). Los
 *                valores están en el intervalo [0,1]
 * @pre valores debe contener la dirección de memoria de un bloque correctamente
 *      alojado
 */
void Scene::getColorBack ( GLfloat* valores )
{
   valores[0] = _backgroundColor[0];
   valores[1] = _backgroundColor[1];
   valores[2] = _backgroundColor[2];
   valores[3] = _backgroundColor[3];
}


/**
 * Método para asignar el color de fondo de la escena
 * @param valores Dirección de memoria de un bloque de cuatro valores desde los
 *                que se copiarán las componentes de color (R, G, B, A)
 * @pre valores debe contener la dirección de memoria de un bloque correctamente
 *      alojado, y los valores almacenados deben estar en el intervalo [0,1]
 */
void Scene::setColorBack ( GLfloat* valores )
{
   _backgroundColor[0] = valores[0];
   _backgroundColor[1] = valores[1];
   _backgroundColor[2] = valores[2];
   _backgroundColor[3] = valores[3];

   glClearColor ( _backgroundColor[0], _backgroundColor[1], _backgroundColor[2],
                  _backgroundColor[3] );
}


/**
 * Método para asignar el color de fondo de la escena
 * @param r Color de la componente roja del color
 * @param g Color de la componente verde del color
 * @param b Color de la componente azul del color
 * @param a Color de la componente de transparencia del color
 * @pre Los valores de r, g, b y a han de estar en el rango [0,1]
 */
void Scene::setColorBack ( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
   _backgroundColor[0] = r;
   _backgroundColor[1] = g;
   _backgroundColor[2] = b;
   _backgroundColor[3] = a;

   glClearColor ( _backgroundColor[0], _backgroundColor[1], _backgroundColor[2],
                  _backgroundColor[3] );
}


/**
 * Método para activar el Z-buffer
 */
void Scene::activateZBuffer ( )
{
   glEnable ( GL_DEPTH_TEST );
   glDepthFunc ( GL_LEQUAL );
}


/**
 * Método para inicializar los parámetros globales de OpenGL
 * @param anchoViewport Ancho del viewport a utilizar
 * @param altoViewport Alto del viewport a utilizar
 */
void Scene::initScene ( GLint anchoViewport, GLint altoViewport )
{
   setColorBack ( 0.9, 0.9, 0.9, 1 );
   activateZBuffer ();
   glEnable ( GL_MULTISAMPLE );
   glEnable ( GL_BLEND );
   changeTamViewport ( anchoViewport, altoViewport );
}


/**
 * Método para añadir un modelo a la escena
 * @pre m almacena la dirección de memoria de un modelo correctamente creado
 */
void Scene::addModel ( Draw* m )
{
   _models.push_back ( m );
}


/**
 * Método para borrar un modelo de la escena
 * @param cual Índice del modelo a eliminar. Su valor está entre 0 y el número
 *        de modelos en la escena menos 1
 * @throw std::runtime_error Si la escena no tiene modelos
 * @throw std::invalid_argument Si el valor del índice no se corresponde con
 *        ningún modelo de la escena
 */
void Scene::deleteModel ( int cual )
{
   if ( _models.empty () )
   {
      throw std::runtime_error ( "Scene::borraModelo: el modelo no existe" );
   }

   if ( ( cual < 0 ) || ( cual >= _models.size () ) )
   {
      throw std::invalid_argument ( "Scene::borraModelo: índice incorrecto" );
   }

   delete ( _models[cual] );
   _models[cual] = nullptr;
   _models.erase ( _models.begin () + cual );
}



/**
 * Método para consultar un modelo de la escena
 * @param cual Índice del modelo a eliminar. Su valor está entre 0 y el número
 *        de modelos en la escena menos 1
 * @return La dirección de memoria donde se guarda el modelo consultado
 * @throw std::runtime_error Si no hay modelos en la escena
 * @throw std::invalid_argument Si el valor del índice no se corresponde con
 *        ningún modelo de la escena
 */
Draw* Scene::getModel ( int cual )
{
   if ( _models.empty () )
   {
      throw std::runtime_error ( "Scene::getModelo: no hay modelos" );
   }

   if ( ( cual < 0 ) || ( cual >= _models.size () ) )
   {
      throw std::invalid_argument ( "Scene::getModelo: índice incorrecto" );
   }

   return _models[cual];
}


/**
 * Método para consultar el número de modelos en la escena actualmente
 * @return El número de modelos en la escena
 */
int Scene::getNumModels ()
{
   return _models.size ();
}


/**
 * Método para "resetear" la cámara virtual y colocarla en una de las vistas
 * estándar (planta, alzado, perfil o isométrica)
 * @param v Identificador de la vista que se quiere aplicar
 */
void Scene::setView ( TypeView v )
{
   _camera.setView ( v );
}


/**
 * Método para mover la cámara virtual
 * @param m Identifica el tipo de movimiento a aplicar
 * @param factor Magnitud del movimiento a aplicar
 */
void Scene::moveCamera ( Movements m, GLfloat factor )
{
   switch ( m )
   {
      case Movements::CRANE:
         _camera.crane ( factor );
         break;
      case Movements::PAN:
         _camera.pan ( factor );
         break;
      case Movements::TILT:
         _camera.tilt ( factor );
         break;
      case Movements::ZOOM:
         _camera.zoom ( factor );
      default:
         break;
   }
}


/**
 * Método para mover la cámara virtual
 * @param m Identifica el tipo de movimiento a aplicar
 * @param factor1 Primer factor de magnitud del movimiento a aplicar
 * @param factor2 Segundo factor de magnitud del movimiento a aplicar
 */
void Scene::moveCamera ( Movements m, GLfloat factor1,
                                  GLfloat factor2 )
{
   switch ( m )
   {
      case Movements::DOLLY:
         _camera.dolly ( factor1, factor2 );
         break;
      case Movements::ORBIT:
         _camera.orbit ( factor1, factor2 );
         break;
   }
}


/**
 * Método para asignar el modo de visualización del modelo activo
 * @param modelo Índice del modelo a cambiar. Su valor ha de estar entre 0 y el
 *        número de modelos en la escena menos 1
 * @param m Modo de visualización a aplicar (alambre, sólido, texturizado...)
 * @throw std::runtime_error Si hay algún error
 *
 */
void Scene::setDrawMode ( int modelo, TypeDraw modo )
{
   Draw* m;

   try
   {
      m = getModel ( modelo );
   }
   catch ( std::runtime_error& e )
   {
      std::string mensaje = "setModoDibujo -> ";
      throw std::runtime_error ( mensaje + e.what () );
   }
   catch ( std::invalid_argument& e )
   {
      std::string mensaje = "setModoDibujo -> ";
      throw std::runtime_error ( mensaje  + e.what () );
   }

   if ( m == nullptr )
   {
      throw std::runtime_error ( "setModoDibujo: no hay modelo" );
   }

   m->setDrawMode ( modo );
}


/**
 * Método para añadir una fuente de luz a la escena
 * @param nueva Fuente de luz a añadir
 * @post Se crea una copia de la fuente de luz. No se mantiene ningún vínculo
 *       con la que se pasa como parámetro
 */
void Scene::addLight ( Light& nueva )
{
   _lights.push_back ( nueva );
}
