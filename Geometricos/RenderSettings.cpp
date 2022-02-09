#include <stdexcept>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "RenderSettings.h"

/**
 * Constructor parametrizado
 * @param tipo Identifica el tipo de luz a crear
 */
Light::Light ( TypeLight tipo ): _type ( tipo )
{ }


/**
 * Constructor de copia
 * @param orig Luz de la que se copian los atributos
 */
Light::Light ( const Light& orig ): _type ( orig._type ), _Ia ( orig._Ia ),
                                        _Id ( orig._Id ), _Is ( orig._Is ),
                                        _position ( orig._position ),
                                        _direction ( orig._direction ),
                                        _gamma ( orig._gamma ), _s ( orig._s )
{ }


/**
 * Destructor
 */
Light::~Light ( )
{ }


/**
 * Cambia el tipo de la luz
 * @param tipo Nuevo tipo a aplicar
 * @return Una referencia al propio objeto, para faciliar el encadenamiento de
 *         llamadas a métodos
 */
Light& Light::setType ( TypeLight type )
{
   this->_type = type;
   return *this;
}


/**
 * Consulta del tipo de luz
 * @return El tipo de luz que se trata
 */
TypeLight Light::getType ( ) const
{
   return _type;
}




/**
 * Método para fijar la dirección de la luz en luces direccionales y focos
 * @param direccion Dirección desde la que proviene la luz, expresada como un
 *        vector que apunta desde la fuente de luz hacia la escena
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas a métodos
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
Light& Light::setDirection ( glm::vec3 direction )
{
   if ( ( _type != TypeLight::SPOT )
        && ( _type != TypeLight::DIRECTIONAL ) )
   {
      throw std::runtime_error ( "Light::setDireccion: tipo de luz incompatible" );
   }

   this->_direction = direction;
   return *this;
}


/**
 * Método para consultar la dirección desde la que proviene la luz en luces
 * direccionales y tipo foco
 * @return La dirección desde la que proviene la luz, expresada como un vector
 *         que apunta desde la fuente de luz hacia la escena
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
glm::vec3 Light::getDirection ( ) const
{
   if ( ( _type != TypeLight::SPOT )
        && ( _type != TypeLight::DIRECTIONAL ) )
   {
      throw std::runtime_error ( "Light::getDireccion: tipo de luz incompatible" );
   }

   return _direction;
}


/**
 * Método para fijar la posición de la fuente de luz en luces de tipo puntual y
 * foco
 * @param posicion Posición de la luz en coordenadas de la escena
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
Light& Light::setPosition ( glm::vec3 posicion )
{
   if ( ( _type != TypeLight::SPOT )
        && ( _type != TypeLight::PUNCTUAL ) )
   {
      throw std::runtime_error ( "Light::setPosicion: tipo de luz incompatible" );
   }

   this->_position = posicion;
   return *this;
}


/**
 * Método para consultar la posición en la que se encuentra la luz en luces de
 * tipo puntual y foco
 * @return La posición de la luz en coordenadas de la escena
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
glm::vec3 Light::getPosition ( ) const
{
   if ( ( _type != TypeLight::SPOT )
        && ( _type != TypeLight::PUNCTUAL ) )
   {
      throw std::runtime_error ( "Light::getPosicion: tipo de luz incompatible" );
   }

   return _position;
}


/**
 * Método para fijar el color (la intensidad) de la luz para el cálculo de los
 * brillos en luces puntuales, direccionales y focos
 * @param Is Color de la luz en formato RGB
 * @pre Los valores de color RGB han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
Light& Light::setIs ( glm::vec3 Is )
{
   if ( _type == TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::setIs: tipo de luz incompatible" );
   }

   this->_Is = Is;
   return *this;
}


/**
 * Método para consultar el color (la intensidad) de la luz para el cálculo de
 * los brillos en luces puntuales, direccionales y focos
 * @return Las coordenadas RGB del color
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
glm::vec3 Light::getIs ( ) const
{
   if ( _type == TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::getIs: tipo de luz incompatible" );
   }

   return _Is;
}


/**
 * Método para fijar el color (la intensidad) de la luz difusa en luces
 * puntuales, direccionales y focos
 * @param Id Coordenadas RGB del color
 * @pre Las coordenadas de color han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
Light& Light::setId ( glm::vec3 Id )
{
   if ( _type == TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::setId: tipo de luz incompatible" );
   }

   this->_Id = Id;
   return *this;
}


/**
 * Método para consultar el color (la intensidad) de la luz difusa en luces
 * puntuales, direccionales y focos
 * @return Las coordenadas RGB del color
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
glm::vec3 Light::getId ( ) const
{
   if ( _type == TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::getId: tipo de luz incompatible" );
   }

   return _Id;
}


/**
 * Método para fijar el color (la intensidad) de la luz ambiente
 * @param Ia Coordenadas RGB del color
 * @pre Los valores de color han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
Light& Light::setIa ( glm::vec3 Ia )
{
   if ( _type != TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::setIa: tipo de luz incompatible" );
   }

   this->_Ia = Ia;
   return *this;
}


/**
 * Método para consultar el color (la intensidad) de la luz ambiente
 * @return Coordenadas RGB del color
 * @throw std::runtime_error Si el tipo de luz no es compatible con este método
 */
glm::vec3 Light::getIa ( ) const
{
   if ( _type != TypeLight::AMBIENT )
   {
      throw std::runtime_error ( "Light::getIa: tipo de luz incompatible" );
   }

   return _Ia;
}


/**
 * Operador de asignación
 * @param orig Objeto del que se copian los datos
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 */
Light& Light::operator = ( const Light& orig )
{
   if ( this != &orig )
   {
      _type = orig._type;
      _Ia = orig._Ia;
      _Id = orig._Id;
      _Is = orig._Is;
      _position = orig._position;
      _direction = orig._direction;
      _gamma = orig._gamma;
      _s = orig._s;
   }

   return *this;
}


Material::Material ( const Material& orig ): _ambient ( orig._ambient ),
                        _diffuse ( orig._diffuse ), _specular ( orig._specular ),
                        _bright ( orig._bright ) //,
                        //_textura ( new Textura ( *orig._textura ) )
{ }


/**
 * Destructor
 * @post Si hay una textura asociada, la destruye
 */
Material::~Material ( )
{
//   if ( _textura != nullptr )
//   {
//      delete ( _textura );
//      _textura = nullptr;
//   }
}


/**
 * Método para consultar el color ambiente
 * @return El color ambiente en formato RGBA
 */
glm::vec4 Material::getAmbient ( )
{
   return _ambient;
}


/**
 * Método para consultar el color difuso
 * @return El color difuso en formato RGBA
 */
glm::vec4 Material::getDiffuse ( )
{
   return _diffuse;
}


/**
 * Método para consultar el color especular
 * @return El color especular en formato RGBA
 */
glm::vec4 Material::getSpecular ( )
{
   return _specular;
}


/**
 * Método para consultar el exponente para el cálculo de los brillos
 * @return El exponente para el cálculo de los brillos
 */
GLfloat Material::getExpBright ( )
{
   return _bright;
}


/**
 * Método para asignar el color ambiente del material
 * @param a Color ambiente a asignar en formato RGBA
 * @pre Las componentes del color han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 */
Material& Material::setAmbient ( glm::vec4 a )
{
   _ambient = a;
   return *this;
}


/**
 * Método para asignar el color difuso del material
 * @param d Color difuso a asignar en formato RGBA
 * @pre Las componentes del color han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 */
Material& Material::setDiffuse ( glm::vec4 d )
{
   _diffuse = d;
   return *this;
}


/**
 * Método para asignar el color especular del material
 * @param e Color especular a asignar en formato RGBA
 * @pre Las componentes del color han de estar en el rango [0,1]
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 */
Material& Material::setSpecular ( glm::vec4 e )
{
   _specular = e;
   return *this;
}


/**
 * Método para asignar el exponente para el cálculo de los brillos
 * @param s Valor del exponente a aplicar
 * @pre El valor de s ha de ser un número positivo
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 */
Material& Material::setExpBright ( GLfloat s )
{
   _bright = s;
   return *this;
}


/**
 * Operador de asignación
 * @param orig Objeto del que se copian los atributos
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @post Si el material tiene una textura asociada, la destruye
 * @post Si el material del que se copian los datos tiene una textura asociada,
 *       se crea una copia de la misma
 */
Material& Material::operator = ( const Material& orig )
{
   if ( this != &orig )
   {
      _ambient = orig._ambient;
      _diffuse = orig._diffuse;
      _specular = orig._specular;
      _bright = orig._bright;

   }

   return *this;
}



GLfloat Camera::PAG_EPSILON = 0.001;

/**
 * Constructor
 * @param pos Posición inicial de la cámara
 * @param lA Punto al que mira la cámara
 */
Camera::Camera ( glm::vec3 pos, glm::vec3 lA ): _posicion ( pos ),
                                                     _lookAt ( lA )
{ }


/**
 * Constructor de copia
 * @param orig Objeto del que copia los parámetros
 */
Camera::Camera ( const Camera& orig ): _posicion ( orig._posicion ),
                    _lookAt ( orig._lookAt ), _fovX ( orig._fovX ),
                    _zNear ( orig._zNear ), _zFar ( orig._zFar ),
                    _width ( orig._width ), _height ( orig._height )
{ }


/**
 * Destructor
 */
Camera::~Camera ( )
{ }


/**
 * Método para consultar la matriz de visión asociada a la cámara
 * @return La matriz de visión tal cual la genera GLM
 */
glm::mat4 Camera::getMvis ( )
{
   return glm::lookAt ( _posicion, _lookAt, vectorUp() ) ;
}


/**
 * Método para consultar la matriz de proyección asociada a la cámara
 * @return La matriz de proyección tal cual la genera GLM
 */
glm::mat4 Camera::getMproy ( )
{
   GLfloat aspecto = _width / _height;
   GLfloat fovY = 2 * atan ( tan ( glm::radians ( _fovX / 2 ) ) / aspecto );

   return glm::perspective ( fovY, aspecto, _zNear, _zFar );
}


/**
 * Método para consultar la matriz resultado de la composición de las
 * transformaciones de visión y proyección
 * @return La matriz resultado de componer las de visión y proyección
 */
glm::mat4 Camera::getMvp ( )
{
   return ( getMproy () * getMvis () );
}


/**
 * Método para aplicar el movimiento pan (panorámica horizontal) a la cámara.
 * Se aplica una rotación del punto al que mira la cámara alrededor de la
 * posición de la cámara. El eje de rotación es el vector V del sistema de
 * coordenadas local de la cámara
 * @param incGradosSex Magnitud de la rotación en grados sexagesimales
 */
void Camera::pan ( GLfloat incGradosSex )
{
   glm::vec3 u, v, n;
   calculateUVN ( u, v, n );

   // Calcula la matriz de rotación
//   glm::mat4 matriz = glm::translate ( _posicion )
//                      * glm::rotate ( glm::radians ( incGradosSex ), v )
//                      * glm::translate ( -_posicion );

   glm::mat4 matriz = glm::translate ( - _posicion );
   matriz = glm::rotate ( matriz, glm::radians (incGradosSex), v );
   matriz = glm::translate ( matriz, _posicion );
   // Aplica la matriz al punto al que mira la cámara
   _lookAt = matriz * glm::vec4 ( _lookAt, 1 );
}


/**
 * Método para aplicar el movimiento tilt (panorámica vertical) a la cámara.
 * Se aplica una rotación del punto al que mira la cámara alrededor de la
 * posición de la cámara. El eje de rotación es el vector U del sistema de
 * coordenadas local de la cámara
 * @param incGradosSex Magnitud de la rotación en grados sexagesimales
 */
void Camera::tilt ( GLfloat incGradosSex )
{
   glm::vec3 u, v, n;
   calculateUVN ( u, v, n );

   // Calcula la matriz de rotación
   glm::mat4 matriz = glm::translate ( -_posicion );
   matriz = glm::rotate ( matriz, glm::radians ( incGradosSex ), u );
   matriz = glm::translate ( matriz, _posicion );

   // Aplica la matriz a la posición de la cámara
   _lookAt = matriz * glm::vec4 ( _lookAt, 1 );
}


/**
 * Método para aplicar el movimiento dolly a la cámara.
 * Se aplican sendas traslaciones en los ejes X y Z de la escena sobre la
 * posición de la cámara y el punto al que mira
 * @param incX Unidades de desplazamiento en el eje X de la escena
 * @param incZ Unidades de desplazamiento en el eje Z de la escena
 */
void Camera::dolly ( GLfloat incX, GLfloat incZ )
{
   _posicion[0] += incX;
   _posicion[2] += incZ;
   _lookAt[0] += incX;
   _lookAt[2] += incZ;
}


/**
 * Método para aplicar el movimiento crane a la cámara.
 * Se aplica una traslación en el eje Y de la escena sobre la posición de la
 * cámara y el punto al que mira
 * @param incY Unidades de desplazamiento a aplicar
 */
void Camera::crane ( GLfloat incY )
{
   _posicion[1] += incY;
   _lookAt[1] += incY;
}


/**
 * Método para aplicar el movimiento orbit a la cámara.
 * Se aplican dos rotaciones (latitud y longitud) a la cámara con respecto al
 * punto al que mira
 * @param incGradosSexLat Magnitud de la rotación en latitud en grados sexagesimales
 * @param incGradosSexLon Magnitud de la rotación en longitud en grados sexagesimales
 */
void Camera::orbit ( GLfloat incGradosSexLat, GLfloat incGradosSexLon )
{
   glm::vec3 u, v, n;
   calculateUVN ( u, v, n );

   glm::mat4 matriz = glm::translate ( -_lookAt );
   matriz = glm::rotate ( matriz, glm::radians ( incGradosSexLat ), u );
   matriz = glm::rotate ( matriz, glm::radians ( incGradosSexLon ), v );
   matriz = glm::translate ( matriz, _lookAt );

   _posicion = matriz * glm::vec4 ( _posicion, 1 );
}


/**
 * Método para modificar el zoom (ángulo de visión horizontal) de la cámara
 * @param incGradosSex Magnitud del incremento en grados sexagesimales
 * @post No se permite que el zoom se reduzca a menos de 1 grado, ni que sea
 *       mayor de 180 grados
 */
void Camera::zoom ( GLfloat incGradosSex )
{
   GLfloat aux = _fovX + incGradosSex;
   if ( ( aux >= 1 ) && ( aux <= 180 ) )
   {
      _fovX = aux;
   }
}


/**
 * Método para calcular el sistema de coordenadas local de la cámara
 * @param u A través de este parámetro se devuelve el eje U del sistema de
 *          coordenadas local de la cámara
 * @param v A través de este parámetro se devuelve el eje V del sistema de
 *          coordenadas local de la cámara
 * @param n A través de este parámetro se devuelve el eje N del sistema de
 *          coordenadas local de la cámara
 */
void Camera::calculateUVN ( glm::vec3& u, glm::vec3& v, glm::vec3& n )
{
   n = glm::normalize ( _posicion - _lookAt );

   glm::vec3 up = this->vectorUp ();

   u = glm::normalize ( glm::cross ( up, n ) );
   v = glm::normalize ( glm::cross ( n, u ) );
}


/**
 * Método para calcular el vector UP de la cámara.
 * Este método comprueba si el vector UP coincide con el vector N del sistema
 * de coordenadas local de la cámara. Si coincide, devuelve un vector diferente
 * para los cálculos de matriz de visión y sistema de coordenadas local.
 * @return El vector a utilizar como vector UP para los cálculos
 */
glm::vec3 Camera::vectorUp ( )
{
   glm::vec3 n = glm::normalize ( _posicion - _lookAt );

   // Hay que comprobar si el n coincide con el Y. Si lo hace, lo cambio
   // por el Z. Si no coincide, uso el Y
   glm::vec3 up = glm::vec3 ( 0, 1, 0 );
   if ( glm::all ( glm::epsilonEqual ( n, glm::vec3 ( 0, 1, 0 ),
                                       PAG_EPSILON ) ) )
   {
      up = glm::vec3 ( 0, 0, 1 );
   }
   else
   {
      if ( glm::all ( glm::epsilonEqual ( n, glm::vec3 ( 0, -1, 0 ),
                                          PAG_EPSILON ) ) )
      {
         up = glm::vec3 ( 0, 0, -1 );
      }
   }

   return up;
}


/**
 * Método para consultar la posición de la cámara
 * @return La posición de la cámara en la escena
 */
glm::vec3 Camera::getPos ( )
{
   return _posicion;
}


/**
 * Método para consultar el punto al que mira la cámara
 * @return El punto al que mira la cámara en la escena
 */
glm::vec3 Camera::getLA ( )
{
   return _lookAt;
}


/**
 * Método para consultar el ángulo de visión de la cámara
 * @return El ángulo de visión de la cámara
 */
GLfloat Camera::getFov ( )
{
   return _fovX;
}


/**
 * Método para consultar la distancia a la que se encuentra el plano zNear
 * @return Distancia a la que se encuentra el plano zNear de la cámara
 */
GLfloat Camera::getZnear ( )
{
   return _zNear;
}


/**
 * Método para consultar la distancia a la que se encuentra el plano zFar
 * @return Distancia a la que se encuentra el plano zFar de la cámara
 */
GLfloat Camera::getZfar ( )
{
   return _zFar;
}


/**
 * Método para consultar las dimensiones del viewport de la cámara
 * @param ancho En este parámetro se almacenará el ancho del viewport
 * @param alto En este parámetro se almacenará el alto del viewport
 */
void Camera::getViewport ( GLfloat& ancho, GLfloat& alto )
{
   ancho = _width;
   alto = _height;
}


/**
 * Método para cambiar directamente la posición de la cámara
 * @param pos Nueva posición de la cámara en la escena
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 */
Camera& Camera::setPos ( glm::vec3 pos )
{
   _posicion = pos;
   return *this;
}


/**
 * Método para cambiar directamente el punto al que mira la cámara
 * @param lA Nueva posición del punto al que mira la cámara en la escena
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 */
Camera& Camera::setLA ( glm::vec3 lA )
{
   _lookAt = lA;
   return *this;
}


/**
 * Método para cambiar directamente el zoom de la cámara
 * @param fov Nuevo valor de zoom
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 */
Camera& Camera::setFov ( GLfloat fov )
{
   if ( fov <= 0 )
   {
      throw std::invalid_argument ( "Camara::setFov: el valor ha de ser"
                                    " positivo" );
   }

   _fovX = fov;
   return *this;
}


/**
 * Método para asignar los planos zNear y zFar de la cámara
 * @param zN Nueva distancia a la que se encuentra el plano zNear
 * @param zFar Nueva distancia a la que se encuentra el plano zFar
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 * @throw std::invalid_argument Si zN o zF son negativos, o si zF es menor o
 *                              igual que zN
 */
Camera& Camera::setRangeZ ( GLfloat zN, GLfloat zF )
{
   if ( zN <= 0 )
   {
      throw std::invalid_argument ( "Camara::setRangoZ: el valor de zNear"
                                    " ha de ser positivo" );
   }

   if ( zF <= 0 )
   {
      throw std::invalid_argument ( "Camara::setRangoZ: el valor de zFar ha"
                                    " de ser positivo" );
   }

   if ( zF <= zN )
   {
      throw std::invalid_argument ( "Camara::setRangoZ: el valor de zFar ha"
                                    " de ser mayor que el valor de zNear" );
   }

   _zNear = zN;
   _zFar = zF;
   return *this;
}


/**
 * Método para cambiar las dimensiones del viewport de la cámara
 * @param ancho Nuevo ancho del viewport
 * @param alto Nuevo alto del viewport
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 * @throw std::invalid_argument Si el ancho o el alto que se pasan como
 *                              parámetros no son positivos
 */
Camera& Camera::setViewport ( GLfloat ancho, GLfloat alto )
{
   if ( ancho <= 0 )
   {
      throw std::invalid_argument ( "Camara::setViewport: el ancho del"
                                    " viewport ha de ser positivo" );
   }

   if ( alto <= 0 )
   {
      throw std::invalid_argument ( "Camara::setViewport: el alto del"
                                    " viewport ha de ser positivo" );
   }

   _width = ancho;
   _height = alto;
   return *this;
}


/**
 * Método para "resetear" la posición y el punto al que mira la cámara, según
 * las vistas estándar (planta, alzado, perfil o isométrica)
 * @param v Identifica la vista a la que se quiere volver
 * @return Una referencia al mismo objeto, para facilitar el encadenamiento de
 *         llamadas a métodos
 */
Camera& Camera::setView ( TypeView v )
{
   switch (v)
   {
      case TypeView::ELEVATION:
         _posicion = glm::vec3 ( 0, 0, 10 );
         _lookAt = glm::vec3 ( 0, 0, 0 );
         break;
      case TypeView::PLANT:
         _posicion = glm::vec3 ( 0, 10, 0 );
         _lookAt = glm::vec3 ( 0, 0, 0 );
         break;
      case TypeView::PROFILE:
         _posicion = glm::vec3 ( 10, 0, 0 );
         _lookAt = glm::vec3 ( 0, 0, 0 );
         break;
      case TypeView::ISOMETRIC:
         _posicion = glm::vec3 ( 10, 10, 10 );
         _lookAt = glm::vec3 ( 0, 0, 0 );
         break;
   }

   return *this;
}

