#pragma once

#include <gl/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "ShaderProgram.h"
#include "RenderSettings.h"


namespace GEO
{
	struct TypeColor;

	/**
	* @brief Enumeración para los tipos de modelos a gestionar
	*/
	
	struct TypeColor{
		float R,G,B;
		TypeColor (): R(0), G(0), B(0){}
		TypeColor (float RR, float  GG, float BB): R(RR), G(GG), B(BB){}
		TypeColor (glm::vec3 col): R(col[0]), G(col[1]), B(col[2]) {}
		TypeColor (glm::vec4 col): R(col[0]), G(col[1]), B(col[2]) {}
		glm::vec3 getVec3 () const { return {R,G,B}; }
		glm::vec4 getVec4 () const { return {R,G,B,1.0};}
	};

	// Colores
	const TypeColor green(0, 1, 0);
	const TypeColor blue(0, 0, 1);
	const TypeColor red(1, 0, 0);

	const TypeColor magenta(1, 0, 1);
	const TypeColor cyan(0, 1, 1);
	const TypeColor yellow(1, 1, 0);

	const TypeColor orange(1, .5f, 0);
	const TypeColor lime(.5f, 1, 0);
	const TypeColor turquesa(0, 1, .5f);
	const TypeColor lightblue(0, .5f, 1);
	const TypeColor purple(.5f, 0, 1);
	const TypeColor pink(1, 0, .5f);

	const TypeColor maroon(.5f, 0, 0);
	const TypeColor olive(.5f, .5f, 0);
	const TypeColor darkgreen(0, .1f, 0);
	const TypeColor darkpurple(.5f, 0, .5f);
	const TypeColor teal(0, .5f, .5f);
	const TypeColor navy(0, 0, .5f);

	const TypeColor white(1, 1, 1);
	const TypeColor black(0, 0, 0);
	const TypeColor grey(.5f, .5f, .5f);
	const TypeColor darkgrey(.2f, .2f, .2f);
	const TypeColor silver(.8f, .8f, .8f);

	const TypeColor brown(.6f, .3f, 0.05f);
	
	static std::vector<TypeColor> colors {
		red, blue, green, magenta, yellow, cyan, orange, lime, turquesa,
		lightblue, purple, pink, maroon, olive, darkgreen, darkpurple, teal, navy, darkgrey, grey, silver
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
	  WIREFRAME = 1,
	  PLAIN = 2,
	  POINT = 3,
	  LINE = 4,
	  POLYGON = 5,
	  TRANSPARENCY = 6,
	  LITPLAIN = 7,
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

   public:
		void buildVAO ();
		void creaVAO2 ();
		void processNodeAssimp ( aiNode* node, const aiScene* scene );
		void processMeshAssimp ( aiMesh* mesh, const aiScene* scene );
		void setShader (const Light& l, glm::mat4 matrizV, glm::mat4 mvIT ) const;
		void cleaning ();

	public:
		Draw ();
		Draw ( const TypeModel& type, std::string pathfile );
		Draw ( const Draw& orig );
		virtual ~Draw ( );

		Draw& setShaderProgram ( const std::string& name );

		void render ( glm::mat4 matrixVP) const;
		void renderLit ( glm::mat4 matrixV, glm::mat4 matrixVP, const Light& l) const;

		void setDrawMode ( TypeDraw m ) { _mode = m; }
		void setMaterial ( const Material& m ) { _material = m; }
		void setAmbient ( glm::vec3 a ) { _material.setAmbient(glm::vec4(a, 1.f)); }
		void setAmbient ( glm::vec4 a ) { _material.setAmbient(a); }
		void setDiffuse ( glm::vec3 d ) { _material.setDiffuse(glm::vec4(d, 1.f));; }
		void setDiffuse ( glm::vec4 d ) { _material.setDiffuse(d); }
		void setEspecular ( glm::vec3 e ) { _material.setSpecular(glm::vec4(e, 1.f)); }
		void setSpecular ( glm::vec4 e ) { _material.setSpecular(e); }
		void setExpBright ( GLfloat s ) { _material.setExpBright(s); }
	
		void setColorActivo (glm::vec4 col) { colorAct = col; }
		void setColorActivo (glm::vec3 col) { colorAct = glm::vec4(col, 1.f); }
		void setColorActivo (TypeColor col) { colorAct = col; }

		void apply ( glm::mat4 t ) { _tModeling = t * _tModeling; }

		Draw& loadFile ( std::string pathfile );

		TypeDraw getDrawMode() const { return _mode; }

		void addVertices(std::vector<glm::vec3> vertices);
		std::vector<glm::vec3> getVertices() const { return _vertices; }
		int getNumVertices() const { return _vertices.size(); }

		void addNormal(float x, float y, float z);
		void addDefaultNormals(int numNormals);

		void addIndex(int i);
		void addSequencialIndices(int numIndices, int initialIndex = 0);
   };
}

