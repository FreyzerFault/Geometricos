
/* 
 * File:   RenderSettings.h
 * Author: lidia|algarcia
 *
 * Created on 9 de enero de 2021, 18:45
 */

#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H


#include "windows.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

   /// Tipos de luz
   enum class TypeLight
   {
      AMBIENT,      ///< Luz ambiente
      PUNCTUAL,       ///< Luz puntual
      DIRECTIONAL,   ///< Luz direccional
      SPOT           ///< Foco de luz
   };
   
   enum class TypeView
   {
      PLANT,      ///< Vista desde el eje Y positivo
      ELEVATION,      ///< Vista desde el eje Z positivo
      PROFILE,      ///< Vista desde el eje X positivo
      ISOMETRIC   ///< Vista desde la "diagonal principal"
   };
   
   /// Movimientos de cámara estándar
   enum class Movements
   {
      NONE,   ///< No hay movimiento
      PAN,    ///< Movimiento panorámico horizontal
      TILT,   ///< Movimiento panorámico vertical
      DOLLY,   ///< Movimiento en X y Z de la escena
      CRANE,   ///< Movimiento en Y de la escena
      ORBIT,   ///< Movimiento alrededor del punto al que se mira
      ZOOM   ///< Aumento/decremento del ángulo de visión
   };


   /**
    * @brief Luz
    * 
    * Los objetos de esta clase representan luces virtuales. El tipo de luz
    * es parametrizable. Según el tipo de luz, algunos parámetros serán válidos
    * y otros no.
    */
   class Light
   {
      private:
        TypeLight _type = TypeLight::AMBIENT;   ///< Tipo de luz
        glm::vec3 _Ia = {0,0,0};   ///< Intensidad de luz ambiente
        glm::vec3 _Id = {0,0,0};   ///< Intensidad de luz difusa
        glm::vec3 _Is = {0,0,0};   ///< Intensidad de luz especular
        glm::vec3 _position = {0,0,0};   ///< Posición de la luz
        /** Dirección de procedencia de la luz (direccional) o hacia donde se
         *  orienta la luz (foco) */
        glm::vec3 _direction = {0,0,0};
        GLfloat _gamma = 0;   ///< Ángulo de apertura del cono de luz (grados sexagesimales)
        GLfloat _s = 0;   ///< Exponente para el decaimiento del cono de luz
      public:
         Light ( ) = default;
         Light ( TypeLight tipo );
         Light ( const Light& orig );
         virtual ~Light ( );
         Light& setType ( TypeLight tipo );
         TypeLight getType ( ) const;
//         Light& setS ( GLfloat s );
//         GLfloat getS ( ) const;
//         Light& setGamma ( GLfloat gamma );
//         GLfloat getGamma ( ) const;
         Light& setDirection ( glm::vec3 direccion );
         glm::vec3 getDirection ( ) const;
         Light& setPosition ( glm::vec3 posicion );
         glm::vec3 getPosition ( ) const;
         Light& setIs ( glm::vec3 Is );
         glm::vec3 getIs ( ) const;
         Light& setId ( glm::vec3 Id );
         glm::vec3 getId ( ) const;
         Light& setIa ( glm::vec3 Ia );
         glm::vec3 getIa ( ) const;
         Light& operator= ( const Light& orig );
   };
   
   
   
   
   class Material
   {
      private:
         glm::vec4 _ambient = { 0, 0, 0, 1 };   ///< Color ambiente
         glm::vec4 _diffuse = { 0, 0, 0, 1 };   ///< Color difuso
         glm::vec4 _specular = { 0, 0, 0, 1 };   ///< Color especular
         GLfloat _bright = 0;   ///< Exponente para el cálculo de los brillos
        // Textura* _textura = nullptr;   ///< Imagen de textura

      public:
         Material ( ) = default;
         Material ( const Material& orig );
         virtual ~Material ( );
         Material& setAmbient ( glm::vec4 a );
         Material& setDiffuse ( glm::vec4 d );
         Material& setSpecular ( glm::vec4 e );
         Material& setExpBright ( GLfloat s );
         glm::vec4 getAmbient ();
         glm::vec4 getDiffuse ();
         glm::vec4 getSpecular ();
         GLfloat getExpBright ();
         Material& operator= ( const Material& orig );
   };
   
   
   /**
    * @brief Cámara virtual
    * 
    * Cada objeto de esta clase guardará toda la información necesaria para
    * configurar y utilizar una cámara virtual en una escena
    */
   class Camera
   {
      private:
         static GLfloat PAG_EPSILON;   ///< Precisón para comparación de vectores
         glm::vec3 _posicion = {10, 10, 10};   ///< Posición en la escena
         glm::vec3 _lookAt = {0, 0, 0};   ///< Punto al que mira
         GLfloat _fovX = 40;   ///< Ángulo de visión en X (en grados sexagesimales)
         GLfloat _zNear = 1;   ///< Distancia del plano zNear
         GLfloat _zFar = 20;   ///< Distancia del plano zFar
         GLfloat _width = 0;   ///< Ancho del viewport
         GLfloat _height = 1;   ///< Alto del viewport
         
         void calculateUVN ( glm::vec3& u, glm::vec3& v, glm::vec3& n );
         glm::vec3 vectorUp ();

      public:
         Camera ( ) = default;
         Camera ( glm::vec3 pos, glm::vec3 lA );
         Camera ( const Camera& orig );
         virtual ~Camera ( );
         glm::mat4 getMvis ();
         glm::mat4 getMproy ();
         glm::mat4 getMvp ();
         void pan ( GLfloat incGradosSex );
         void tilt ( GLfloat incGradosSex );
         void dolly ( GLfloat incX, GLfloat incZ );
         void crane ( GLfloat incY );
         void orbit ( GLfloat incGradosSexLat, GLfloat incGradosSexLon );
         void zoom ( GLfloat incGradosSex );
         glm::vec3 getPos ();
         glm::vec3 getLA ();
         GLfloat getFov ();
         GLfloat getZnear ();
         GLfloat getZfar ();
         void getViewport ( GLfloat& ancho, GLfloat& alto );
         Camera& setPos ( glm::vec3 pos );
         Camera& setLA ( glm::vec3 lA );
         Camera& setFov ( GLfloat fov );
         Camera& setRangeZ ( GLfloat zN, GLfloat zF );
         Camera& setViewport ( GLfloat ancho, GLfloat alto );
         Camera& setView ( TypeView v );
   };
   
   

  




#endif /* RENDERSETTINGS_H */

