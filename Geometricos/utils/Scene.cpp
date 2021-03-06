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


GEO::Scene* GEO::Scene::_instance = nullptr;

/**
 * Destructor.
 * Elimina los modelos, si los hubiera
 */
GEO::Scene::~Scene()
{
	if (!_models.empty())
	{
		for (Draw* m : _models)
		{
			if (m != nullptr)
			{
				delete m;
				m = nullptr;
			}
		}
	}
}


void GEO::Scene::setScene(GLint anchoViewport, GLint altoViewport)
{
	initScene(anchoViewport, altoViewport);
	Light l;
	l.setType(TypeLight::AMBIENT)
	 .setIa(glm::vec3(.2, .2, .2));
	getInstance()->addLight(l);
	l.setType(TypeLight::PUNCTUAL)
	 .setId(glm::vec3(1, 1, 1))
	 .setIs(glm::vec3(1, 1, 1))
	 .setPosition(glm::vec3(-1.5, .25, .25));
	getInstance()->addLight(l);
	l.setType(TypeLight::DIRECTIONAL)
	 .setId(glm::vec3(1, 1, 1))
	 .setIs(glm::vec3(1, 1, 1))
	 .setDirection(glm::vec3(0, 1, 1));
	getInstance()->addLight(l);
	l.setType(TypeLight::SPOT)
	 .setId(glm::vec3(1, 1, 1))
	 .setIs(glm::vec3(1, 1, 1))
	 .setPosition(glm::vec3(1.5, 1.5, 1.5))
	 .setDirection(glm::vec3(-1, -1, -1))
	.setGamma(30)
	.setS(0.5);
	getInstance()->addLight(l);
	getInstance()->setView(TypeView::ELEVATION);
}

/**
 * Método para consultar la instancia única de la clase
 * @return Un puntero a la instancia única de la clase
 * @throw std::runtime_error Si hay algún error
 */
GEO::Scene* GEO::Scene::getInstance()
{
	if (!_instance)
	{
		try
		{
			_instance = new Scene;
		}
		catch (std::runtime_error& e)
		{
			const std::string mensaje = "Scene::getInstancia ->\n";
			throw std::runtime_error(mensaje + e.what());
		}
	}

	return _instance;
}


/**
 * Método para hacer el refresco de la escena
 * @throw std::runtime_error Si hay algún error
 */
void GEO::Scene::refresh()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (!_models.empty())
	{
		const glm::mat4 mV = _camera.getMvis();
		const glm::mat4 mVP = _camera.getMvp();

		try
		{
			// First Pass GL_ONE_MINUS_SRC_ALPHA
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			for (Draw* m : _models)
			{
				if (!m)
					continue;

				switch (m->getDrawMode())
				{
				case TypeDraw::LINE:
				case TypeDraw::POINT:
				case TypeDraw::POLYGON:
				case TypeDraw::PLAIN:
				case TypeDraw::WIREFRAME:
					m->render(mVP);
					break;
				case TypeDraw::LITPLAIN:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					for (auto& _light : _lights)
					{
						m->renderLit(mV, mVP, _light);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					}
					break;
				case TypeDraw::TRANSPARENCY:
					// Los modelos con transparencia se dibujan despues de los demas
					break;
				}
			}

			for (Draw* m : _models)
			{
				if (m && m->getDrawMode() == TypeDraw::TRANSPARENCY)
					m->render(mVP);
			}
		}
		catch (std::runtime_error& e)
		{
			const std::string mensaje = "Scene::refrescar -> ";
			throw std::runtime_error(mensaje + e.what());
		}
	}
}


/**
 * Método para cambiar el tamaño del viewport
 * @param ancho Ancho del nuevo viewport
 * @param alto Alto del nuevo viewport
 * @pre Tanto alto como ancho deben ser valores positivos
 */
void GEO::Scene::changeTamViewport(GLint ancho, GLint alto)
{
	_camera.setViewport(ancho, alto);
	glViewport(0, 0, ancho, alto);
}


/**
 * Método para consultar el color de fondo de la escena
 * @param valores Dirección de memoria de un bloque de cuatro valores a los que
 *                se le copiarán las componentes del color (R, G, B, A). Los
 *                valores están en el intervalo [0,1]
 * @pre valores debe contener la dirección de memoria de un bloque correctamente
 *      alojado
 */
void GEO::Scene::getColorBack(GLfloat* valores)
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
void GEO::Scene::setColorBack(GLfloat* valores)
{
	_backgroundColor[0] = valores[0];
	_backgroundColor[1] = valores[1];
	_backgroundColor[2] = valores[2];
	_backgroundColor[3] = valores[3];

	glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2],
				 _backgroundColor[3]);
}


/**
 * Método para asignar el color de fondo de la escena
 * @param r Color de la componente roja del color
 * @param g Color de la componente verde del color
 * @param b Color de la componente azul del color
 * @param a Color de la componente de transparencia del color
 * @pre Los valores de r, g, b y a han de estar en el rango [0,1]
 */
void GEO::Scene::setColorBack(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_backgroundColor[0] = r;
	_backgroundColor[1] = g;
	_backgroundColor[2] = b;
	_backgroundColor[3] = a;

	glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2],
				 _backgroundColor[3]);
}


/**
 * Método para activar el Z-buffer
 */
void GEO::Scene::activateZBuffer()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}


/**
 * Método para inicializar los parámetros globales de OpenGL
 * @param anchoViewport Ancho del viewport a utilizar
 * @param altoViewport Alto del viewport a utilizar
 */
void GEO::Scene::initScene(GLint anchoViewport, GLint altoViewport)
{
	setColorBack(0.9, 0.9, 0.9, 1);
	activateZBuffer();
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	changeTamViewport(anchoViewport, altoViewport);
}


/**
 * Método para añadir un modelo a la escena
 * @pre m almacena la dirección de memoria de un modelo correctamente creado
 */
void GEO::Scene::addModel(Draw* m)
{
	_models.push_back(m);
}


/**
 * Método para borrar un modelo de la escena
 * @param cual Índice del modelo a eliminar. Su valor está entre 0 y el número
 *        de modelos en la escena menos 1
 * @throw std::runtime_error Si la escena no tiene modelos
 * @throw std::invalid_argument Si el valor del índice no se corresponde con
 *        ningún modelo de la escena
 */
void GEO::Scene::deleteModel(int cual)
{
	if (_models.empty())
	{
		throw std::runtime_error("Scene::borraModelo: el modelo no existe");
	}

	if ((cual < 0) || (cual >= _models.size()))
	{
		throw std::invalid_argument("Scene::borraModelo: índice incorrecto");
	}

	delete (_models[cual]);
	_models[cual] = nullptr;
	_models.erase(_models.begin() + cual);
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
GEO::Draw* GEO::Scene::getModel(int cual) const
{
	if (_models.empty())
	{
		throw std::runtime_error("Scene::getModelo: no hay modelos");
	}

	if ((cual < 0) || (cual >= _models.size()))
	{
		throw std::invalid_argument("Scene::getModelo: índice incorrecto");
	}

	return _models[cual];
}


/**
 * Método para consultar el número de modelos en la escena actualmente
 * @return El número de modelos en la escena
 */
int GEO::Scene::getNumModels() const
{
	return _models.size();
}


/**
 * Método para "resetear" la cámara virtual y colocarla en una de las vistas
 * estándar (planta, alzado, perfil o isométrica)
 * @param v Identificador de la vista que se quiere aplicar
 */
void GEO::Scene::setView(TypeView v)
{
	_camera.setView(v);
}


/**
 * Método para mover la cámara virtual
 * @param m Identifica el tipo de movimiento a aplicar
 * @param factor Magnitud del movimiento a aplicar
 */
void GEO::Scene::moveCamera(Movements m, GLfloat factor)
{
	switch (m)
	{
	case Movements::CRANE:
		_camera.crane(factor);
		break;
	case Movements::PAN:
		_camera.pan(factor);
		break;
	case Movements::TILT:
		_camera.tilt(factor);
		break;
	case Movements::ZOOM:
		_camera.zoom(factor);
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
void GEO::Scene::moveCamera(Movements m, GLfloat factor1,
							GLfloat factor2)
{
	switch (m)
	{
	case Movements::DOLLY:
		_camera.dolly(factor1, factor2);
		break;
	case Movements::ORBIT:
		_camera.orbit(factor1, factor2);
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
void GEO::Scene::setDrawMode(int modelo, TypeDraw modo)
{
	Draw* m;

	try
	{
		m = getModel(modelo);
	}
	catch (std::runtime_error& e)
	{
		const std::string mensaje = "setModoDibujo -> ";
		throw std::runtime_error(mensaje + e.what());
	}
	catch (std::invalid_argument& e)
	{
		const std::string mensaje = "setModoDibujo -> ";
		throw std::runtime_error(mensaje + e.what());
	}

	if (m == nullptr)
	{
		throw std::runtime_error("setModoDibujo: no hay modelo");
	}

	m->setDrawMode(modo);
}


/**
 * Método para añadir una fuente de luz a la escena
 * @param nueva Fuente de luz a añadir
 * @post Se crea una copia de la fuente de luz. No se mantiene ningún vínculo
 *       con la que se pasa como parámetro
 */
void GEO::Scene::addLight(Light& nueva)
{
	_lights.push_back(nueva);
}
