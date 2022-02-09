/** 
 * @file PAGrenderer.h
 * @author algarcia
 *
 * @date 28 de septiembre de 2020, 12:19
 * 
 * @brief Declaración de la clase PAGrenderer
 */

#ifndef PAGRENDERER_H
#define PAGRENDERER_H

#include "windows.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "Draw.h"
#include "RenderSettings.h"

/**
    * @brief Clase encargada de encapsular toda la gestión del área de dibujo
    *        OpenGL.
    * 
    * Esta clase coordina todo el renderizado de las escenas OpenGL. Se
    * implementa aplicando el patrón de diseño Singleton. Está pensada para que
    * las funciones callback hagan llamadas a sus métodos
    */
   class Scene
   {
      private:
         static Scene* _instance;   ///< Dirección del objeto único de la clase
         GLfloat _backgroundColor[4] = {0,0,0,0};   ///< Color de fondo de la escena
         std::vector<Draw*> _models;   ///< Modelos a visualizar
         Camera _camera;   ///< Cámara a utilizar
         std::vector<Light> _lights;   ///< Luces de la escena

         Scene () = default;

      public:
         virtual ~Scene ( );
         static Scene* getInstance ();
         void setScene (GLint widthViewport, GLint heightViewport);
         void refresh ();
         void changeTamViewport ( GLint width, GLint height );
         void getColorBack ( GLfloat* values );
         void setColorBack ( GLfloat* values );
         void setColorBack ( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
         void activateZBuffer ();
         void initScene ( GLint widthViewport, GLint heightViewport );
         void addModel ( Draw* m );
         void deleteModel ( int cual );
         Draw* getModel ( int cual );
         int getNumModels ();
         void setView ( TypeView v );
         void moveCamera ( Movements m, GLfloat factor );
         void moveCamera ( Movements m, GLfloat factor1, GLfloat factor2 );
         void setDrawMode ( int model, TypeDraw mode );
         void addLight ( Light& newer );
   };

#endif /* PAGRENDERER_H */

