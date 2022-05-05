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

static std::runtime_error errMsg(std::runtime_error& e, const std::string& func)
{
	return std::runtime_error(func + " -> " + e.what());
}

/**
 * Constructor de la clase. Carga la geometría y el VAO para OpenGL.
 * Este constructor crea geometrías simples, de las definidas en la clase
 * TipoModelo
 *
 * @param tipo Tipo del modelo a crear
 * @throw std::invalid_argument Si el tipo no es correcto
 */

GEO::Draw::Draw()
{
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
GEO::Draw::Draw(const TypeModel& type, std::string pathFile)
{
	switch (type)
	{
	case TypeModel::OBJ:
		try
		{
			loadFile(pathFile);
		}
		catch (std::runtime_error& e)
		{
			const std::string mensaje = "Model -> ";
			throw std::runtime_error(mensaje + e.what());
		}
		break;
	default:
		throw std::invalid_argument("Model: tipo incorrecto");
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
GEO::Draw::Draw(const Draw& orig): _vertices(orig._vertices),
								   _normals(orig._normals),
								   //_cTextura ( orig._cTextura ),
								   _indices(orig._indices),
								   _mode(orig._mode),
								   _material(orig._material),
								   _tModeling(orig._tModeling)
{
	if (orig._program != nullptr)
	{
		_program = new ShaderProgram(*(orig._program));
	}

	buildVAO();
}


/**
 * Destructor.
 * Borra el VAO, y si hay un shader program asociado al modelo, también lo
 * destruye
 */
GEO::Draw::~Draw()
{
	glDeleteBuffers(1, &_idVBO);
	glDeleteBuffers(1, &_idIBO);
	glDeleteBuffers(1, &_idVBOnorm);
	if (_idVBOcTex != 0)
	{
		glDeleteBuffers(1, &_idVBOcTex);
	}
	glDeleteVertexArrays(1, &_idVAO);

	if (_program != nullptr)
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
void GEO::Draw::buildVAO()
{
	// Crea el VAO y lo activa
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);

	// VBO para vértices
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3),
				 _vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
						  nullptr);
	glEnableVertexAttribArray(0);

	// VBO para normales
	glGenBuffers(1, &_idVBOnorm);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBOnorm);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3),
				 _normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
						  nullptr);
	glEnableVertexAttribArray(1);


	// IBO
	glGenBuffers(1, &_idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint),
				 _indices.data(), GL_STATIC_DRAW);
}



/**
 * Carga un nuevo shader program para el modelo, leyendo los shaders desde
 * archivos
 * @param name Nombre base para los archivos. A este nombre se le añadirán
 *               sufijos (por ejemplo "-vs.glsl") para vertex shader y fragment
 *               shader
 * @return Una referencia al propio modelo, para permitir el encadenamiento de
 *         llamadas
 * @throw std::runtime_error Si hay algún error cargando los shaders
 * @post Si el modelo tenía un shader asignado previamente, lo destruye
 */
GEO::Draw& GEO::Draw::setShaderProgram(const std::string& name)
{
	delete _program;

	try
	{
		_program = new ShaderProgram(name);
	}
	catch (std::runtime_error& e)
	{
		throw errMsg(e, "Draw::setShaderProgram");
	}

	return *this;
}

void GEO::Draw::render(glm::mat4 matrixVP) const
{
	if (!_program)
	{
		throw std::runtime_error("Draw::render: el modelo no tiene un"
			" shader program asignado");
	}

	try
	{
		_program->activate();
		_program->setUniform("matrizMVP", matrixVP * _tModeling);
		glBindVertexArray(_idVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);

		_program->setUniform("micolor", _mode == TypeDraw::TRANSPARENCY ? glm::vec4(colorAct.getVec3(), 0.3f) : colorAct.getVec4());
		_program->selectRoutine(GL_FRAGMENT_SHADER, "colorElegido",
								"colorBasico");
		_program->selectRoutine(GL_FRAGMENT_SHADER, "colorCalculado",
								"unlit");
		_program->applyRoutines(GL_FRAGMENT_SHADER);

		glEnable(GL_BLEND);

		switch (_mode)
		{
		case TypeDraw::WIREFRAME:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
			break;
		case TypeDraw::LINE:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_LINE_STRIP, _indices.size(), GL_UNSIGNED_INT, nullptr);
			break;
		case TypeDraw::POLYGON:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_LINE_LOOP, _indices.size(), GL_UNSIGNED_INT, nullptr);
			break;
		case TypeDraw::POINT:
			glDisable(GL_BLEND);

			glEnable(GL_PROGRAM_POINT_SIZE_EXT);
			glPointSize(2);
			glDrawElements(GL_POINTS, _indices.size(), GL_UNSIGNED_INT, nullptr);
			break;
		case TypeDraw::TRANSPARENCY:
		case TypeDraw::PLAIN:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
			break;
		default:
			break;
		}
	}
	catch (std::runtime_error& e)
	{
		throw errMsg(e, "Draw::render(matrixMVP)");
	}
}


/**
 * Método para dibujar el modelo
 * @param matrixV Matriz de visión que hay que aplicar al modelo
 * @param matrixVP Composición de las matrices de proyección y visión que hay
 *        que aplicar al modelo
 * @param l Luz con la que se ilumina el modelo
 * @throw std::runtime_error Si hay algún error
 */


void GEO::Draw::renderLit(glm::mat4 matrixV, glm::mat4 matrixVP, const Light& l) const
{
	if (_program == nullptr)
	{
		throw std::runtime_error("Draw::render: el modelo no tiene un"
			" shader program asignado");
	}

	try
	{
		const glm::mat4 mModVisP = matrixVP * _tModeling;
		const glm::mat4 mModVis = matrixV * _tModeling;
		const glm::mat4 mModVisIT = transpose(inverse(mModVis));
		const glm::mat4 mVisIT = transpose(inverse(matrixV));
		_program->activate();
		_program->setUniform("matrizMVP", mModVisP)
				.setUniform("matrizMV", mModVis)
				.setUniform("matrizMVit", mModVisIT);
		glBindVertexArray(_idVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
		

		// Iluminacion
		setShader(l, matrixV, mVisIT);
		glEnable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
	}
	catch (std::runtime_error& e)
	{
		throw errMsg(e, "Draw::render(matrixV, matrixVP, l)");
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
void GEO::Draw::setShader(const Light& l, glm::mat4 matrizV, glm::mat4 mvIT) const
{
	const TypeLight aux = l.getType();
	try
	{
		switch (aux)
		{
		case TypeLight::AMBIENT:
			_program->selectRoutine(GL_FRAGMENT_SHADER, "colorElegido",
								"colorAmbiente");
			_program->selectRoutine(GL_FRAGMENT_SHADER, "colorCalculado",
									"luzAmbiente");
			_program->applyRoutines(GL_FRAGMENT_SHADER);
			_program->setUniform("materialId", _material.getAmbient());
			_program->setUniform("luzIa", l.getIa());
			break;
		case TypeLight::PUNCTUAL:
			{
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorElegido",
									"colorMaterial");
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorCalculado",
										"luzPuntual");
				_program->applyRoutines(GL_FRAGMENT_SHADER);
				const glm::vec3 pos = matrizV * glm::vec4(l.getPosition(), 1);
				_program->setUniform("luzPos", pos)
						.setUniform("luzId", l.getId())
						.setUniform("luzIs", l.getIs())
						.setUniform("materialId", _material.getDiffuse())
						.setUniform("materialIs", _material.getSpecular())
						.setUniform("materialExp", _material.getExpBright());
				break;
			}
		case TypeLight::DIRECTIONAL:
			{
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorElegido",
									"colorMaterial");
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorCalculado",
										"luzDireccional");
				_program->applyRoutines(GL_FRAGMENT_SHADER);
				glm::vec3 dir = mvIT * glm::vec4(l.getDirection(), 0);
				dir = normalize(dir);
				_program->setUniform("luzDir", dir)
						.setUniform("luzId", l.getId())
						.setUniform("luzIs", l.getIs())
						.setUniform("materialId", _material.getDiffuse())
						.setUniform("materialIs", _material.getSpecular())
						.setUniform("materialExp", _material.getExpBright());
				break;
			}
		case TypeLight::SPOT:
			{
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorElegido",
									"colorMaterial");
				_program->selectRoutine(GL_FRAGMENT_SHADER, "colorCalculado",
										"luzFoco");
				_program->applyRoutines(GL_FRAGMENT_SHADER);
				glm::vec3 dir = mvIT * glm::vec4(l.getDirection(), 0);
				dir = normalize(dir);
				const glm::vec3 pos = matrizV * glm::vec4(l.getPosition(), 1);
				_program->setUniform("luzPos", pos)
						.setUniform("luzDir", dir)
						.setUniform("luzId", l.getId())
						.setUniform("luzIs", l.getIs())
						.setUniform("materialId", _material.getDiffuse())
						.setUniform("materialIs", _material.getSpecular())
						.setUniform("materialExp", _material.getExpBright())
						.setUniform("luzGamma", l.getGamma())
						.setUniform("luzS", l.getS());
				break;
			}
		}
	}
	catch (std::runtime_error& e)
	{
		throw errMsg(e, "Draw::ajustarShader");
	}
}



/**
 * Carga la geometría de un archivo
 * @param pathfile
 * @param rutaArchivo Ubicación donde se encuentra el archivo con la geometría.
 *        La información ha de estar en un formato soportado por Assimp para
 *        que pueda cargarse.
 * @return Una referencia al propio objeto
 * @throw std::runtime_error Si hay algún problema en la carga
 * @post Si el modelo tuviera otra geometría previa, se elimina antes de la
 *       carga
 * @post Una vez cargada la geometría, se genera el VAO para dibujar el modelo
 */
GEO::Draw& GEO::Draw::loadFile(const std::string pathfile)
{
	cleaning();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pathfile,
											 aiProcess_JoinIdenticalVertices
											 | aiProcess_Triangulate
											 | aiProcess_GenSmoothNormals);
	//                                                 | aiProcess_GenNormals);

	// Carga to lo que haya en el archivo como un único modelo
	if (!scene || !scene->mRootNode
		|| (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
	{
		const std::string mensaje = "Draw::cargarArchivo: error cargando el archivo "
			+ pathfile + " -> " + importer.GetErrorString();
		throw std::runtime_error(mensaje);
	}

	processNodeAssimp(scene->mRootNode, scene);

	buildVAO();

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
void GEO::Draw::processNodeAssimp(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* malla = scene->mMeshes[node->mMeshes[i]];
		processMeshAssimp(malla, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNodeAssimp(node->mChildren[i], scene);
	}
}


/**
 * Carga en el modelo la geometría de una malla creada por Assimp al importar
 * un archivo
 * @param malla Malla creada por Assimp
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @post Carga vértices, normales, coordenadas de textura (si hubiera) e índices
 */
void GEO::Draw::processMeshAssimp(aiMesh* mesh, const aiScene* scene)
{
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 v;
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;
		_vertices.push_back(v);

		glm::vec3 n;
		n.x = mesh->mNormals[i].x;
		n.y = mesh->mNormals[i].y;
		n.z = mesh->mNormals[i].z;
		_normals.push_back(n);

		//      if ( malla->mTextureCoords[0] )
		//      {
		//         glm::vec2 ct;
		//         ct.x = malla->mTextureCoords[0][i].x;
		//         ct.y = malla->mTextureCoords[0][i].y;
		//         _cTextura.push_back ( ct );
		//      }
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace cara = mesh->mFaces[i];
		for (int j = 0; j < cara.mNumIndices; j++)
		{
			_indices.push_back(cara.mIndices[j]);
		}
	}
}


/**
 * Método para eliminar la geometría que hubiera cargada en el modelo, así como
 * los buffers de OpenGL asociados
 */
void GEO::Draw::cleaning()
{
	_vertices.clear();
	_normals.clear();
	//   _cTextura.clear ();
	_indices.clear();

	if (_idVAO != 0)
	{
		glDeleteBuffers(1, &_idVBO);
		glDeleteBuffers(1, &_idIBO);
		glDeleteBuffers(1, &_idVBOnorm);
		if (_idVBOcTex != 0)
		{
			glDeleteBuffers(1, &_idVBOcTex);
		}
		glDeleteVertexArrays(1, &_idVAO);
	}
}

void GEO::Draw::addVertices(std::vector<glm::vec3> vertices)
{
	_vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}

void GEO::Draw::addNormal(float x, float y, float z)
{
	_normals.emplace_back(x, y, z);
}

void GEO::Draw::addDefaultNormals(int numNormals)
{
	for (int i = 0; i < numNormals; ++i)
	{
		_normals.emplace_back(0, 0, 1);
	}
}

void GEO::Draw::addIndex(int i)
{
	_indices.push_back(i);
}

void GEO::Draw::addSequencialIndices(int numIndices, int initialIndex)
{
	for (int i = initialIndex; i < numIndices + initialIndex; ++i)
	{
		_indices.push_back(i);
	}
}
