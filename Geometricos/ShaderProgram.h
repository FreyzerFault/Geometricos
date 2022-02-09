/** 
 * @file PAGshaderProgram.h
 * @author algarcia
 *
 * @date 8 de octubre de 2020, 12:03
 * 
 * @brief Declaración de la clase PAGshaderProgram
 */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "windows.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

   /**
    * @brief Clase para gestionar los shader programs
    * 
    * Esta clase es la responsable de la carga, compilación, enlazado y activación
    * de los shader programs, compuestos por un vertex shader y un fragment shader
    */
   class ShaderProgram
   {
      private:
         GLuint _idVS = 0;   ///< Identificador del vertex shader
         GLuint _idFS = 0;   ///< Identificador del fragment shader
         GLuint _idSP = 0;   ///< Identificador del shader program
         bool _ready = false;   ///< Estado del shader program
         /// Implementaciones de subrutinas seleccionadas para el fragment shader
         std::vector<GLuint> _subroutinesFS;
         /// Implementaciones de subrutinas seleccionadas para el vertex shader
         std::vector<GLuint> _subroutinesVS;

         void loadShader ( std::string archivo, GLenum tipo );

      public:
         /// Constructor por defecto
         ShaderProgram ( ) = default;
         ShaderProgram ( std::string name );
         ShaderProgram ( const ShaderProgram& orig );
         virtual ~ShaderProgram ( );
         void loadProgram ( std::string name );
         bool isReady ();
         void activate ();
         ShaderProgram& setUniform ( std::string name, glm::mat4 value );
         ShaderProgram& setUniform ( std::string name, glm::vec4 value );
         ShaderProgram& setUniform ( std::string name, glm::vec3 value );
         ShaderProgram& setUniform ( std::string name, GLfloat value );
         ShaderProgram& setUniform ( std::string name, GLint value );
         void selectRoutine ( GLenum typeShader, std::string uniformName,
                               std::string implementationName );
         void applyRoutines ( GLenum shaderType );
   };

#endif /* PAGSHADERPROGRAM_H */

