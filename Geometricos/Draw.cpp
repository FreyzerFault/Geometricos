/**
 * @file Draw.cpp
 * @author algarcia|lidia
 *
 * @date 18 de octubre de 2020, 10:53
 *
 * @brief Implementación de los métodos de la clase PAGmodelo
 */

#include <stdexcept>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Draw.h"
#include "RenderSettings.h"

/**
 * Constructor de la clase. Carga la geometría y el VAO para OpenGL.
 * Este constructor crea geometrías simples, de las definidas en la clase
 * TipoModelo
 *
 * @param tipo Tipo del modelo a crear
 * @throw std::invalid_argument Si el tipo no es correcto
 */

Draw::Draw (){
    
}



/**
 * Constructor de la clase. Carga la geometría y el VAO para OpenGL.
 * Este constructor es el indicado para importar archivos.
 *
 * @param tipo Tipo del modelo a crear
 * @param rutaArchivo Ruta donde se encuentra un archivo del que cargar la
 *        geometría
 * @throw std::invalid_argument Si el tipo no es correcto
 * @throw std::runtime_error Si hay algún problema en la carga del archivo
 */
Draw::Draw ( const TypeModel& type, std::string pathFile )
{
   switch ( type )
   {
      case TypeModel::OBJ:
         try
         {
            loadFile ( pathFile );
         }
         catch ( std::runtime_error& e )
         {
            std::string mensaje = "Model -> ";
            throw std::runtime_error ( mensaje + e.what () );
         }
         break;
      default:
         throw std::invalid_argument ( "Model: tipo incorrecto" );
         break;
   }
}


/**
 * Constructor de copia. Carga la geometría y el VAO para OpenGL
 * @param orig Modelo a copiar
 * @post Se copian vértices, atributos y material, y si el modelo tiene un shader
 *       program asociado, también crea una copia de éste
 * @post Se crea un nuevo VAO para el modelo
 */
Draw::Draw ( const Draw& orig ): _vertices ( orig._vertices ),
                                                 _normals ( orig._normals ),
                                                 //_cTextura ( orig._cTextura ),
                                                 _indices ( orig._indices ),
                                                 _mode ( orig._mode ),
                                                 _material ( orig._material ),
                                                 _tModeling ( orig._tModeling )
{
   if ( orig._program != nullptr )
   {
      _program = new ShaderProgram ( *(orig._program) );
   }

   buildVAO ();
}


/**
 * Destructor.
 * Borra el VAO, y si hay un shader program asociado al modelo, también lo
 * destruye
 */
Draw::~Draw ( )
{
   glDeleteBuffers ( 1, &_idVBO );
   glDeleteBuffers ( 1, &_idIBO );
   glDeleteBuffers ( 1, &_idVBOnorm );
   if ( _idVBOcTex != 0 )
   {
      glDeleteBuffers ( 1, &_idVBOcTex );
   }
   glDeleteVertexArrays ( 1, &_idVAO );

   if ( _program != nullptr )
   {
      delete _program;
      _program = nullptr;
   }
}



/**
 * Crea el VAO para OpenGL.
 * Los VBOs se crean en formato no entrelazado. Si hay coordenadas de textura
 * en el modelo, también crea un VBO con ellas
 */
void Draw::buildVAO ( )
{
   // Crea el VAO y lo activa
   glGenVertexArrays ( 1, &_idVAO );
   glBindVertexArray ( _idVAO );

   // VBO para vértices
   glGenBuffers ( 1, &_idVBO );
   glBindBuffer ( GL_ARRAY_BUFFER, _idVBO );
   glBufferData ( GL_ARRAY_BUFFER, _vertices.size () * sizeof ( glm::vec3 ),
                  _vertices.data (), GL_STATIC_DRAW );
   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, sizeof ( glm::vec3 ),
                           nullptr );
   glEnableVertexAttribArray ( 0 );

   // VBO para normales
   glGenBuffers ( 1, &_idVBOnorm );
   glBindBuffer ( GL_ARRAY_BUFFER, _idVBOnorm );
   glBufferData ( GL_ARRAY_BUFFER, _normals.size () * sizeof ( glm::vec3 ),
                  _normals.data (), GL_STATIC_DRAW );
   glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE, sizeof ( glm::vec3 ),
                           nullptr );
   glEnableVertexAttribArray ( 1 );


   // IBO
   glGenBuffers ( 1, &_idIBO );
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _idIBO );
   glBufferData ( GL_ELEMENT_ARRAY_BUFFER, _indices.size () * sizeof(GLuint),
                  _indices.data (), GL_STATIC_DRAW );
}



/**
 * Carga un nuevo shader program para el modelo, leyendo los shaders desde
 * archivos
 * @param nombre Nombre base para los archivos. A este nombre se le añadirán
 *               sufijos (por ejemplo "-vs.glsl") para vertex shader y fragment
 *               shader
 * @return Una referencia al propio modelo, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si hay algún error cargando los shaders
 * @post Si el modelo tenía un shader asignado previamente, lo destruye
 */
Draw& Draw::setShaderProgram ( const std::string& nombre )
{
   if ( _program != nullptr )
   {
      delete _program;
   }

   try
   {
      _program = new ShaderProgram ( nombre );
   }
   catch ( std::runtime_error& e )
   {
      std::string message = "Draw::setShaderProgram -> ";
      throw std::runtime_error ( message + e.what () );
   }

   return *this;
}


/**
 * Método para dibujar el modelo
 * @param matrizV Matriz de visión que hay que aplicar al modelo
 * @param matrizVP Composición de las matrices de proyección y visión que hay
 *        que aplicar al modelo
 * @param l Luz con la que se ilumina el modelo
 * @throw std::runtime_error Si hay algún error
 */


void Draw::render ( glm::mat4 matrizV, glm::mat4 matrizVP, Light& l )
{
   if ( _program == nullptr )
   {
      throw std::runtime_error ( "Draw::render: el modelo no tiene un"
                                 " shader program asignado" );
   }

   try
   {
      glm::mat4 mModVisP = matrizVP * _tModeling;
      glm::mat4 mModVis = matrizV * _tModeling;
      glm::mat4 mModVisIT = glm::transpose ( glm::inverse ( mModVis ) );
      glm::mat4 mVisIT = glm::transpose ( glm::inverse ( matrizV ) );
      _program->activate ();
      _program->setUniform ( "matrizMVP", mModVisP )
                .setUniform ( "matrizMV", mModVis )
                .setUniform ( "matrizMVit", mModVisIT );
      glBindVertexArray ( _idVAO );
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _idIBO );

      glm::vec4 color; 
      switch ( _mode )
      {
         case TypeDraw::WIREFRAME:
             color  =  colorAct.getVec4();
            _program->setUniform ( "micolor", color );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorElegido",
                                        "colorMaterial" );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "colorMio" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            
            glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
            glDrawElements ( GL_TRIANGLES, _indices.size (), GL_UNSIGNED_INT, nullptr );
            break;
         
         case TypeDraw::LINE:
             color  =  colorAct.getVec4();
            _program->setUniform ( "micolor", color );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorElegido",
                                        "colorMaterial" );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "colorMio" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            
            glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
            glDrawElements ( GL_LINE_STRIP, _indices.size (), GL_UNSIGNED_INT, nullptr );
            break;
          
        case TypeDraw::PolygonGeo:
             color  =  colorAct.getVec4();
            _program->setUniform ( "micolor", color );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorElegido",
                                        "colorMaterial" );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "colorMio" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            
            glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
            glDrawElements ( GL_LINE_LOOP, _indices.size (), GL_UNSIGNED_INT, nullptr );
            break;    
            
            
         case TypeDraw::POINT:
             color  =  colorAct.getVec4();
            _program->setUniform ( "micolor", color );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorElegido",
                                        "colorMaterial" );
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "colorMio" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            
            
            glEnable(GL_PROGRAM_POINT_SIZE_EXT);
            glPointSize(4);
            glDrawElements ( GL_POINTS, _indices.size (), GL_UNSIGNED_INT, nullptr );
            break;       
            

         case TypeDraw::PLAIN:
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorElegido",
                                        "colorMaterial" );
            setShader ( l, matrizV, mVisIT );
            glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
            glDrawElements ( GL_TRIANGLES, _indices.size (), GL_UNSIGNED_INT, nullptr );
            break;
      }

      
   }
   catch ( std::runtime_error& e )
   {
      std::string mensaje = "Draw::render -> ";
      throw std::runtime_error ( mensaje + e.what () );
   }
}




/**
 * Método para activar subrutinas y pasar uniforms al shader program según
 * el tipo de luz
 * @param l Luz a utilizar en el rendering
 * @param matrizV Matriz de visión a aplicar en el rendering
 * @param mvIT Traspuesta de la inversa de la matriz de visión a aplicar en el
 *        rendering
 * @throw std::runtime_error
 */
void Draw::setShader ( Light& l, glm::mat4 matrizV, glm::mat4 mvIT )
{
   TypeLight aux = l.getType ();
   try
   {
      switch ( aux )
      {
         case TypeLight::AMBIENT:
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "luzAmbiente" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            _program->setUniform ( "materialId", _material.getAmbient () );
            _program->setUniform ( "luzIa", l.getIa () );
            break;
         case TypeLight::PUNCTUAL:
         {
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "luzPuntual" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            glm::vec3 pos = matrizV * glm::vec4 ( l.getPosition (), 1 );
            _program->setUniform ( "luzPos", pos )
                      .setUniform ( "luzId", l.getId () )
                      .setUniform ( "luzIs", l.getIs () )
                      .setUniform ( "materialId", _material.getDiffuse () )
                      .setUniform ( "materialIs", _material.getSpecular () )
                      .setUniform ( "materialExp", _material.getExpBright () );
            break;
         }
         case TypeLight::DIRECTIONAL:
         {
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "luzDireccional" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            glm::vec3 dir = mvIT * glm::vec4 ( l.getDirection (), 0 );
            dir = glm::normalize ( dir );
            _program->setUniform ( "luzDir", dir )
                      .setUniform ( "luzId", l.getId () )
                      .setUniform ( "luzIs", l.getIs () )
                      .setUniform ( "materialId", _material.getDiffuse () )
                      .setUniform ( "materialIs", _material.getSpecular () )
                      .setUniform ( "materialExp", _material.getExpBright () );
            break;
         }
         case TypeLight::SPOT:
         {
            _program->selectRoutine ( GL_FRAGMENT_SHADER, "colorCalculado",
                                        "luzFoco" );
            _program->applyRoutines ( GL_FRAGMENT_SHADER );
            glm::vec3 dir = mvIT * glm::vec4 ( l.getDirection (), 0 );
            dir = glm::normalize ( dir );
            glm::vec3 pos = matrizV * glm::vec4 ( l.getPosition (), 1 );
            _program->setUniform ( "luzPos", pos )
                      .setUniform ( "luzDir", dir )
                      .setUniform ( "luzId", l.getId () )
                      .setUniform ( "luzIs", l.getIs () )
                      .setUniform ( "materialId", _material.getDiffuse () )
                      .setUniform ( "materialIs", _material.getSpecular () )
                      .setUniform ( "materialExp", _material.getExpBright () );
            break;
         }
      }
   }
   catch ( std::runtime_error& e )
   {
      std::string mensaje = "Draw::ajustarShader -> ";
      throw std::runtime_error ( mensaje + e.what () );
   }
}


/**
 * Método para fijar cómo se va a dibujar el modelo
 * @param m Modo de dibujado (alambre, sólido, texturizado...)
 * @return Una referencia al propio modelo, para permitir el encadenamiento de
 *         llamadas
 * @post El modo de visualización TEXTURA sólo se activa si el modelo tiene
 *       realmente asignada una textura
 */
Draw& Draw::setDrawMode ( TypeDraw m )
{
   switch ( m )
   {
      case TypeDraw::POINT:  
      case TypeDraw::WIREFRAME:
      case TypeDraw::PLAIN:
      case TypeDraw::LINE:
      case TypeDraw::PolygonGeo:
          
         _mode = m;
   }

   return *this;
}


/**
 * Método para asignar un material al modelo
 * @param m Propiedades del material a aplicar
 * @pre Se asume que m es un material válido
 * @return Una referencia al propio objeto, para permitir el encadenamiento de
 *         llamadas
 * @post Se copia la información de m en el material del modelo. No se mantiene
 *       ninguna vinculación con m
 */
Draw& Draw::setMaterial ( const Material& m )
{
   _material = m;
   return *this;
}


/**
 * Método para asignar el color ambiente del modelo
 * @param a Color a asignar en formato RGBA. Los valores de las componentes
 *        están en el rango [0,1]
 * @pre Se asume que las componentes del color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setAmbient ( glm::vec4 a )
{
   _material.setAmbient ( a );
   return *this;
}


/**
 * Método para asignar el color ambiente del modelo
 * @param a Color a asignar en formato RGB. Los valores de las componentes de
 *          color están en el rango [0,1]. Se asume que el valor de alfa es 1
 * @pre Se asume que las componentes de color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setAmbient ( glm::vec3 a )
{
   _material.setAmbient ( glm::vec4 ( a, 1 ) );
   return *this;
}


/**
 * Método para asignar el color difuso del modelo
 * @param d Color a asignar en formato RGBA. Los valores de las componentes de
 *          color están en el rango [0,1]
 * @pre Se asume que las componentes de color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setDiffuse ( glm::vec4 d )
{
   _material.setDiffuse ( d );
   return *this;
}


/**
 * Método para asignar el color difuso del modelo
 * @param d Color a asignar en formato RGB. Los valores de las componentes de
 *          color están en el rango [0,1]. Se asume que el valor de alfa es 1
 * @pre Se asume que las componentes de color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setDiffuse ( glm::vec3 d )
{
   _material.setDiffuse ( glm::vec4 ( d, 1 ) );
   return *this;
}


/**
 * Método para asignar el color especular del modelo
 * @param e Color a asignar en formato RGBA. Los valores de las componentes de
 *          color están en el rango [0,1]
 * @pre Se asume que las componentes de color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setSpecular ( glm::vec4 e )
{
   _material.setSpecular ( e );
   return *this;
}


/**
 * Método para asignar el color especular del modelo
 * @param e Color a asignar en formato RGB. Los valores de las componentes de
 *          color están en el rango [0,1]. Se asume que el valor de alfa es 1
 * @pre Se asume que las componentes de color tienen valores correctos
 * @return Una referencia al propio objeto
 */
Draw& Draw::setEspecular ( glm::vec3 e )
{
   _material.setSpecular ( glm::vec4 ( e, 1 ) );
   return *this;
}


/**
 * Método para asignar el exponente para el cálculo de los brillos
 * @param s El nuevo valor de exponente a aplicar
 * @return Una referencia al propio objeto
 */
Draw& Draw::setExpBright ( GLfloat s )
{
   _material.setExpBright ( s );
   return *this;
}


/**
 * Método para aplicar una transformación al modelo
 * @param t Matriz de transformación a aplicar
 * @pre Se asume que t es una matriz de transformación válida
 * @post t se acumula a las transformaciones que previamente pudiera tener el
 *       modelo
 * @return Una referencia al propio objeto
 */
Draw& Draw::apply ( glm::mat4 t )
{
   _tModeling = t * _tModeling;
   return *this;
}


/**
 * Carga la geometría de un archivo
 * @param rutaArchivo Ubicación donde se encuentra el archivo con la geometría.
 *        La información ha de estar en un formato soportado por Assimp para
 *        que pueda cargarse.
 * @return Una referencia al propio objeto
 * @throw std::runtime_error Si hay algún problema en la carga
 * @post Si el modelo tuviera otra geometría previa, se elimina antes de la
 *       carga
 * @post Una vez cargada la geometría, se genera el VAO para dibujar el modelo
 */
Draw& Draw::loadFile ( std::string pathfile )
{
   cleaning ();

   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile ( pathfile,
                                                   aiProcess_JoinIdenticalVertices
                                                 | aiProcess_Triangulate
                                                 | aiProcess_GenSmoothNormals);
//                                                 | aiProcess_GenNormals);

   // Carga todo lo que haya en el archivo como un único modelo
   if ( !scene || !scene->mRootNode
        || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) )
   {
      std::string mensaje = "Draw::cargarArchivo: error cargando el archivo "
                            + pathfile + " -> " + importer.GetErrorString ();
      throw std::runtime_error ( mensaje );
   }

   processNodeAssimp ( scene->mRootNode, scene );

   buildVAO ();

   return *this;
}


/**
 * Método para procesar de manera recursiva un nodo de la estructura creada por
 * Assimp al cargar un archivo
 * @param nodo Nodo de la estructura de Assimp a procesar
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @note Al procesar el nodo de manera recursiva, no se garantiza que se llegue
 *       a un desbordamiento de pila
 */
void Draw::processNodeAssimp ( aiNode* node, const aiScene* scene )
{
   for ( int i = 0; i < node->mNumMeshes; i++ )
   {
      aiMesh* malla = scene->mMeshes[node->mMeshes[i]];
      processMeshAssimp ( malla, scene );
   }

   for ( int i = 0; i < node->mNumChildren; i++ )
   {
      processNodeAssimp ( node->mChildren[i], scene );
   }
}


/**
 * Carga en el modelo la geometría de una malla creada por Assimp al importar
 * un archivo
 * @param malla Malla creada por Assimp
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @post Carga vértices, normales, coordenadas de textura (si hubiera) e índices
 */
void Draw::processMeshAssimp (  aiMesh* mesh, const aiScene* scene )
{
   for ( int i = 0; i < mesh->mNumVertices; i++ )
   {
      glm::vec3 v;
      v.x = mesh->mVertices[i].x;
      v.y = mesh->mVertices[i].y;
      v.z = mesh->mVertices[i].z;
      _vertices.push_back ( v );

      glm::vec3 n;
      n.x = mesh->mNormals[i].x;
      n.y = mesh->mNormals[i].y;
      n.z = mesh->mNormals[i].z;
      _normals.push_back ( n );

//      if ( malla->mTextureCoords[0] )
//      {
//         glm::vec2 ct;
//         ct.x = malla->mTextureCoords[0][i].x;
//         ct.y = malla->mTextureCoords[0][i].y;
//         _cTextura.push_back ( ct );
//      }
   }

   for ( int i = 0; i < mesh->mNumFaces; i++ )
   {
      aiFace cara = mesh->mFaces[i];
      for ( int j = 0; j < cara.mNumIndices; j++ )
      {
         _indices.push_back ( cara.mIndices[j] );
      }
   }
}




/**
 * Método para eliminar la geometría que hubiera cargada en el modelo, así como
 * los buffers de OpenGL asociados
 */
void Draw::cleaning ( )
{
   _vertices.clear ();
   _normals.clear ();
//   _cTextura.clear ();
   _indices.clear ();

   if ( _idVAO != 0 )
   {
      glDeleteBuffers ( 1, &_idVBO );
      glDeleteBuffers ( 1, &_idIBO );
      glDeleteBuffers ( 1, &_idVBOnorm );
      if ( _idVBOcTex != 0 )
      {
         glDeleteBuffers ( 1, &_idVBOcTex );
      }
      glDeleteVertexArrays ( 1, &_idVAO );
   }
}


/**
 * Carga un nuevo shader program para el modelo, leyendo los shaders desde
 * archivos
 * @param nombre Nombre base para los archivos. A este nombre se le añadirán
 *               sufijos (por ejemplo "-vs.glsl") para vertex shader y fragment
 *               shader
 * @return Una referencia al propio modelo, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si hay algún error cargando los shaders
 * @post Si el modelo tenía un shader asignado previamente, lo destruye
 */
Draw& Draw::setColorActivo ( glm::vec4 col )
{
   colorAct = col; 

   return *this;
}


Draw& Draw::setColorActivo ( glm::vec3 col )
{
   colorAct = glm::vec4(col,1.0); 

   return *this;
}

Draw& Draw::setColorActivo ( TypeColor col )
{
   colorAct = col; 

   return *this;
}


