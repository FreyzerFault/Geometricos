/** 
 * @file PAGmodelo.h
 * @authores algarcia|lidia
 *
 * @date 18 de octubre de 2020, 10:53
 * 
 * @brief 
 */

#ifndef DRAW_H
#define DRAW_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "ShaderProgram.h"
#include "RenderSettings.h"

   /**
    * @brief Enumeración para los tipos de modelos a gestionar
    */
    
    struct TypeColor{
        float R,G,B;
        TypeColor (): R(0), G(0), B(0){}
        TypeColor (float RR, float  GG, float BB): R(RR), G(GG), B(BB){}
        TypeColor (glm::vec4 col): R(col[0]), G(col[1]), B(col[2]) {}
        glm::vec4 getVec4 (){ return glm::vec4(R,G,B,1.0);}
    };
    
    
   enum class TypeModel
   {
      TRIANGULAR,   ///< El modelo es un triángulo
      OBJ   ///< El modelo se carga de un archivo estándar (OBJ o similar)
   };
   
   /**
    * @brief Enumeración para los modos de dibujado
    */
   enum class TypeDraw
   {
      WIREFRAME = 1,   ///< El modelo se dibuja en modo de alambre
      PLAIN = 2,   ///< El modelo se dibuja en modo sólido y con sombreado plano
      POINT = 3,
      LINE = 4,
      PolygonGeo = 5,
   };

   /**
    * @brief Clase para gestionar los modelos
    * 
    * Cada objeto de esta clase guarda la información necesaria para gestionar su
    * geometría y su visualización
    */
   class Draw
   {
      protected:
         const float MAXVAL_T = 1000.0; 
         GLuint _idVAO = 0;   ///< Identificador del vertex array object asociado al modelo
         GLuint _idVBO = 0;   ///< Identificador del VBO con el atributo de coordenadas
         GLuint _idIBO = 0;   ///< Identificador del index buffer object
         GLuint _idVBOnorm = 0;   ///< Identificador del VBO con las normales
         GLuint _idVBOcTex = 0;   ///< Identificador del VBO con las coordenadas de textura
         std::vector<glm::vec3> _vertices;   ///< Array con los vértices de la geometría
         std::vector<glm::vec3> _normals;   ///< Array con las normales asociadas a los vértices
         std::vector<GLuint> _indices;   ///< Array con los índices para el dibujado
         TypeDraw _mode = TypeDraw::PLAIN;   ///< Modo en que se va a pintar
         Material _material;   ///< Propiedades del material del modelo
         ShaderProgram* _program = nullptr;   ///< Shader program a utilizar
         glm::mat4 _tModeling = glm::mat4 ( 1 );   ///< Transformación de modelado
         TypeColor colorAct; 

         void buildVAO ();
         void creaVAO2 ();
         void processNodeAssimp ( aiNode* node, const aiScene* scene );
         void processMeshAssimp ( aiMesh* mesh, const aiScene* scene );
         void setShader ( Light& l, glm::mat4 matrizV, glm::mat4 mvIT );
         void cleaning ();

      public:
         Draw ();
         Draw ( const TypeModel& type, std::string pathfile );
         Draw ( const Draw& orig );
         virtual ~Draw ( );
         Draw& setShaderProgram ( const std::string& name );
         void render ( glm::mat4 matrixV, glm::mat4 matrixVP, Light& l);
         Draw& setDrawMode ( TypeDraw m );
         Draw& setMaterial ( const Material& m );
         Draw& setAmbient ( glm::vec3 a );
         Draw& setAmbient ( glm::vec4 a );
         Draw& setDiffuse ( glm::vec3 d );
         Draw& setDiffuse ( glm::vec4 d );
         Draw& setEspecular ( glm::vec3 e );
         Draw& setSpecular ( glm::vec4 e );
         Draw& setExpBright ( GLfloat s );
         Draw& apply ( glm::mat4 t );
         Draw& loadFile ( std::string pathfile );
         Draw& setColorActivo (glm::vec4 col);
         Draw& setColorActivo (glm::vec3 col);
         Draw& setColorActivo (TypeColor col);
   };
   
#endif /* DRAW_H */

