/**
 * @file PAGshaderProgram.cpp
 * @author algarcia
 *
 * @date 8 de octubre de 2020, 12:03
 *
 * @brief Implementación de los métodos de la clase PAGshaderProgram
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <stdexcept>
#include <fstream>
#include <sstream>

#include "ShaderProgram.h"

/**
 * Constructor parametrizado. Crea un shader program cargando un vertex shader
 * y un fragment shader desde ficheros
 * @param nombre Primera parte de los nombres de los ficheros donde están los
 *               shaders. A este texto se le añadirán sufijos ("-vs.glsl" para
 *               el vertex shader, y "-fs.glsl" para el fragment shader)
 * @throw std::runtime_error Si hay algún error
 */
ShaderProgram::ShaderProgram ( std::string nombre )
{
   try
   {
      loadProgram ( nombre );
   }
   catch ( std::runtime_error& e )
   {
      std::string mensaje = "ShaderProgram::ShaderProgram -> ";
      throw std::runtime_error ( mensaje + e.what () );
   }
}

/**
 * Constructor de copia. No crea un nuevo shader program, sino que copia los
 * identificadores OpenGL
 * @param orig Shader program del que copia los atributos
 */
ShaderProgram::ShaderProgram ( const ShaderProgram& orig ):
                                    _idFS ( orig._idFS ), _idSP ( orig._idSP ),
                                    _idVS ( orig._idVS ), _ready ( orig._ready ),
                                    _subroutinesFS ( orig._subroutinesFS ),
                                    _subroutinesVS ( orig._subroutinesVS )
{ }

/**
 * Destructor
 */
ShaderProgram::~ShaderProgram ( )
{
   if ( _idVS != 0 )
   {
      glDeleteShader ( _idVS );
   }

   if ( _idFS != 0 )
   {
      glDeleteShader ( _idFS );
   }

   if ( _idSP != 0 )
   {
      glDeleteProgram ( _idSP );
   }
}

/**
 * Método para comprobar el estado de un shader program
 * @retval true Si el shader program se puede utilizar
 * @retval false Si el shader program no está compilado y enlazado
 */
bool ShaderProgram::isReady ( )
{
   return _ready;
}


/**
 * Método para activar el shader program en OpenGL
 * @throw std::runtime_error Si el shader program no se puede activar
 */
void ShaderProgram::activate ( )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::activate: el shader"
                                 " program no está listo" );
   }

   glUseProgram ( _idSP );
}


/**
 * Método para crear, compilar y enlazar el shader program
 * @throw std::runtime_error Si hay algún problema
 */
void ShaderProgram::loadProgram ( std::string nombre )
{
   try
   {
      loadShader ( nombre + "-vs.glsl", GL_VERTEX_SHADER );
      loadShader ( nombre + "-fs.glsl", GL_FRAGMENT_SHADER );
   }
   catch ( std::runtime_error& e )
   {
      std::string mensaje = "ShaderProgram::cargaPrograma ->\n";
      throw std::runtime_error ( mensaje + e.what () );
   }

   _idSP = glCreateProgram ();
   glAttachShader ( _idSP, _idVS );
   glAttachShader ( _idSP, _idFS );
   glLinkProgram ( _idSP );

   GLint resultado = 0;
   glGetProgramiv ( _idSP, GL_LINK_STATUS, &resultado );
   if ( resultado == GL_FALSE )
   {
      GLint tamMsj = 0;
      std::string mensaje = "";
      glGetProgramiv ( _idSP, GL_INFO_LOG_LENGTH, &tamMsj );

      if ( tamMsj > 0 )
      {
         GLchar* msj = new GLchar[tamMsj];
         GLint escritos = 0;
         glGetProgramInfoLog ( _idSP, tamMsj, &escritos, msj );
         mensaje.assign ( msj );
         delete[] msj;
         msj = nullptr;
      }

      throw std::runtime_error ( "ShaderProgram::cargaPrograma ->\n"
                                 + mensaje );
   }

   // Inicializa los vectores de subrutinas
   GLint tam = 0;
   glGetProgramStageiv ( _idSP, GL_VERTEX_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORMS,
                         &tam );
   _subroutinesVS.resize ( tam, 0 );
   glGetProgramStageiv ( _idSP, GL_FRAGMENT_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORMS,
                         &tam );
   _subroutinesFS.resize ( tam, 0 );

   _ready = true;
}


/**
 * Método para cargar y compilar un shader GLSL
 * @param archivo Ruta completa del archivo con el código GLSL
 * @param tipo Indica el tipo de shader. Los valores aceptados son
 *             GL_VERTEX_SHADER y GL_FRAGMENT_SHADER
 * @throw std::runtime_error Si hay algún problema
 */
void ShaderProgram::loadShader ( std::string file, GLenum type )
{
   if ( ( type != GL_VERTEX_SHADER ) && ( type != GL_FRAGMENT_SHADER ) )
   {
      throw std::runtime_error ( "ShaderProgram::cargaShader: tipo no soportado" );
   }

   std::ifstream fich;
   fich.open ( file );
   if ( !fich.is_open () )
   {
      throw std::runtime_error ( "ShaderProgram::cargaShader: no se puede abrir"
                                 " el archivo " + file );
   }

   std::stringstream streamShader;
   streamShader << fich.rdbuf ();
   std::string fuente = streamShader.str ();
   fich.close ();

   GLuint id = 0;
   GLint result = 0;

   id = glCreateShader ( type );
   const GLchar* fuenteShader = fuente.c_str ();
   glShaderSource ( id, 1, &fuenteShader, nullptr );
   glCompileShader ( id );

   glGetShaderiv ( id, GL_COMPILE_STATUS, &result );
   if ( result == GL_FALSE )
   {
      GLint tamMsj = 0;
      std::string mensaje = "";
      glGetShaderiv ( id, GL_INFO_LOG_LENGTH, &tamMsj );

      if ( tamMsj > 0 )
      {
         GLchar* msj = new GLchar[tamMsj];
         GLint escritos = 0;
         glGetShaderInfoLog ( id, tamMsj, &escritos, msj );
         mensaje.assign ( msj );
         delete[] msj;
         msj = nullptr;
      }

      throw std::runtime_error ( "ShaderProgram::cargaShader ->\n"
                                 + mensaje );
   }

   if ( type == GL_VERTEX_SHADER )
   {
      _idVS = id;
   }
   else
   {
      _idFS = id;
   }
}


/**
 * Método para asignar un parámetro uniform del shader program
 * @param nombre Nombre del parámetro, tal cual aparece en el código GLSL
 * @param valor Valor a asignar al parámetro
 * @throw std::runtime_error Si el shader program no está listo para su uso, o
 *        si el uniform no se ha podido localizar
 */
ShaderProgram& ShaderProgram::setUniform ( std::string name,
                                                     glm::mat4 value )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::setUniform: el shader"
                                 " program no está listo aún" );
   }

   GLint position = glGetUniformLocation ( _idSP, name.c_str () );
   if ( position == -1 )
   {
      std::string message = "ShaderProgram::setUniform: el uniform "
                            + name + " no se ha podido localizar";
      throw std::runtime_error ( message );
   }

   glUniformMatrix4fv ( position, 1, GL_FALSE, &value[0][0] );
   return *this;
}


/**
 * Método para asignar un parámetro uniform del shader program
 * @param nombre Nombre del parámetro, tal cual aparece en el código GLSL
 * @param valor Valor a asignar al parámetro
 * @throw std::runtime_error Si el shader program no está listo para su uso, o
 *        si el uniform no se ha podido localizar
 */
ShaderProgram& ShaderProgram::setUniform ( std::string nombre,
                                                     glm::vec4 valor )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::setUniform: el shader"
                                 " program no está listo aún" );
   }

   GLint posicion = glGetUniformLocation ( _idSP, nombre.c_str () );
   if ( posicion == -1 )
   {
      std::string mensaje = "ShaderProgram::setUniform: el uniform "
                            + nombre + " no se ha podido localizar";
      throw std::runtime_error ( mensaje );
   }

   glUniform4fv ( posicion, 1, &valor[0] );
   return *this;
}


/**
 * Método para asignar un parámetro uniform del shader program
 * @param nombre Nombre del parámetro, tal cual aparece en el código GLSL
 * @param valor Valor a asignar al parámetro
 * @throw std::runtime_error Si el shader program no está listo para su uso, o
 *        si el uniform no se ha podido localizar
 */
ShaderProgram& ShaderProgram::setUniform ( std::string nombre,
                                                     glm::vec3 valor )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::setUniform: el shader"
                                 " program no está listo aún" );
   }

   GLint posicion = glGetUniformLocation ( _idSP, nombre.c_str () );
   if ( posicion == -1 )
   {
      std::string mensaje = "ShaderProgram::setUniform: el uniform "
                            + nombre + " no se ha podido localizar";
      throw std::runtime_error ( mensaje );
   }

   glUniform3fv ( posicion, 1, &valor[0] );
   return *this;
}


/**
 * Método para asignar un parámetro uniform del shader program
 * @param nombre Nombre del parámetro, tal cual aparece en el código GLSL
 * @param valor Valor a asignar al parámetro
 * @throw std::runtime_error Si el shader program no está listo para su uso, o
 *        si el uniform no se ha podido localizar
 */
ShaderProgram& ShaderProgram::setUniform ( std::string nombre,
                                                     GLfloat valor )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::setUniform: el shader"
                                 " program no está listo aún" );
   }

   GLint posicion = glGetUniformLocation ( _idSP, nombre.c_str () );
   if ( posicion == -1 )
   {
      std::string mensaje = "ShaderProgram::setUniform: el uniform "
                            + nombre + " no se ha podido localizar";
      throw std::runtime_error ( mensaje );
   }

   glUniform1f ( posicion, valor );
   return *this;
}


/**
 * Método para asignar un parámetro uniform del shader program
 * @param nombre Nombre del parámetro, tal cual aparece en el código GLSL
 * @param valor Valor a asignar al parámetro
 * @throw std::runtime_error Si el shader program no está listo para su uso, o
 *        si el uniform no se ha podido localizar
 */
ShaderProgram& ShaderProgram::setUniform ( std::string nombre,
                                                     GLint valor )
{
   if ( !_ready )
   {
      throw std::runtime_error ( "ShaderProgram::setUniform: el shader"
                                 " program no está listo aún" );
   }

   GLint posicion = glGetUniformLocation ( _idSP, nombre.c_str () );
   if ( posicion == -1 )
   {
      std::string mensaje = "ShaderProgram::setUniform: el uniform "
                            + nombre + " no se ha podido localizar";
      throw std::runtime_error ( mensaje );
   }

   glUniform1i ( posicion, valor );
   return *this;
}


/**
 * Método para seleccionar una implementación de una subrutina del shader
 * program para su activación
 * @param tipoShader Shader sobre el que se quiere elegir una subrutina
 * @param nombreUniform Nombre del uniform asociado a la subrutina, tal
 *        y como aparece en el código GLSL
 * @param nombreImplementacion Nombre de la implementación de la subrutina que
 *        se quiere seleccionar, tal y como aparece en el código GLSL
 * @throw std::runtime_error Si la subrutina o la implementación no se han
 *        podido localizar
 * @note Este método no activa la implementación elegida. Para esto, hay que
 *       llamar a ShaderProgram::aplicaSubrutinas una vez que se hayan
 *       seleccionado todas las implementaciones a activar
 */
void ShaderProgram::selectRoutine ( GLenum tipoShader,
                                          std::string nombreUniform,
                                          std::string nombreImplementacion )
{
   GLint posUniform = glGetSubroutineUniformLocation ( _idSP, tipoShader,
                                                       nombreUniform.c_str () );
   if ( posUniform == -1 )
   {
      throw std::runtime_error ( "ShaderProgram::eligeSubrutina: no se"
                                 " ha podido localizar el uniform" );
   }

   GLuint aux = glGetSubroutineIndex ( _idSP, tipoShader,
                                       nombreImplementacion.c_str () );

   if ( aux == GL_INVALID_INDEX )
   {
      throw std::runtime_error ( "ShaderProgram::eligeSubrutina: no se"
                                 " ha podido localizar la implementación" );
   }

   if ( tipoShader == GL_FRAGMENT_SHADER )
   {
      _subroutinesFS.at ( posUniform ) = aux;
   }
   else
   {
      _subroutinesVS.at ( posUniform ) = aux;
   }
}


/**
 * Método para activar todas las implementaciones de subrutinas seleccionadas
 * previamente con ShaderProgram::eligeSubrutina
 * @param tipoShader Shader para el que se activan las implementaciones de
 *        subrutinas
 */
void ShaderProgram::applyRoutines ( GLenum tipoShader )
{
   switch ( tipoShader )
   {
      case GL_VERTEX_SHADER:
         glUniformSubroutinesuiv ( tipoShader, _subroutinesVS.size (),
                                   _subroutinesVS.data () );
         break;
      case GL_FRAGMENT_SHADER:
         glUniformSubroutinesuiv ( tipoShader, _subroutinesFS.size (),
                                   _subroutinesFS.data () );
         break;
   }
}