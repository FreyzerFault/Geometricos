# Geometricos

## PRÁCTICA 1

### Point

Para la **Clasificación** del Punto he preferido empezar comprobando si es igual que el punto de origen o destino del segmento de referencia.

    if (equal(p0))
        return PointClassification::ORIGIN;
    if (equal(p1))
        return PointClassification::DEST;

Lo siguiente es comprobar el area del triangulo que forma:

    const double areaTri = triangleArea2(p0, p1) / 2;
	if (areaTri > 0)
		return PointClassification::LEFT;
	if (areaTri < 0)
		return PointClassification::RIGHT;

Y para cuando el punto esta contenido en la linea el Area es 0.

Si el vector a->p y a->b son inversos (sale negativa la multiplicacion) es que está detrás, si no delante.

    if ((a.getX() * b.getX() < 0.0) || (a.getY() * b.getY() < 0.0))
		return PointClassification::BACKWARD;

Para saber si está entre los puntos del segmento o más adelante comparamos el módulo de los vectores:

    if (a > b)
		return PointClassification::FORWARD;
	return PointClassification::BETWEEN;

Para una mejor lógica en operaciones entre puntos y vectores he implementado operadores:

El vector resultante de 2 puntos:

	Vec2D operator-(const Point& v) const;

El punto resultante al sumarle o restarle un Vector:

    virtual Point operator+(const Vec2D& v) const;
    virtual Point operator-(const Vec2D& v) const;



### Vec2D

Al heredar de Point le he añadido tambien operadores matemáticos pero funcionando con Vectores:

    Vec2D operator+(const Vec2D& p) const { return { _x + p.getX(), _y + p.getY() }; }
    Vec2D operator-(const Vec2D& p) const { return { _x - p.getX(), _y - p.getY() }; }
    Vec2D operator*(const double s) const override { return { _x * s, _y * s }; }
    double operator*(const Vec2D& v) const { return (_x * v.getX()) + (_y * v.getY()); }

Además de operadores lógicos para comparar Vectores según la longitud de sus módulos:

    bool operator>(const Point& p) const { return this->getModule() > p.getModule(); }
    bool operator<(const Point& p) const { return this->getModule() < p.getModule(); }
    bool operator==(const Point& p) const { return BasicGeom::equal(getModule(), p.getModule()); }
    bool operator<=(const Point& p) const { return BasicGeom::lequal(getModule(), p.getModule()); }
    bool operator>=(const Point& p) const { return BasicGeom::gequal(getModule(), p.getModule()); }

### SegmentLine

Para la intersección he preferido usar una función que devuelva un puntero a un Punto de intersección en vez de dar un bool (si es nullptr es que no intersecan), además de dar el parámetro t y s de cada recta por referencia:

    GEO::Point* GEO::SegmentLine::intersectionPoint(Point c, Point d, double& s, double& t) const
    {
        Vec2D a = _orig;
        Vec2D b = _dest;

        Vec2D ab = b - a;
        Vec2D cd = d - c;
        Vec2D ac = c - a;

        const double denominador = cd.getX() * ab.getY() - ab.getX() * cd.getY();

        if (BasicGeom::equal(denominador, 0))
        {
            std::cout << "Los segmentos son paralelos, no hay punto de interseccion" << std::endl;
            return nullptr;
        }

        s = (cd.getX() * ac.getY() - ac.getX() * cd.getY()) / denominador;

        t = (ab.getX() * ac.getY() - ac.getX() * ab.getY()) / denominador;

        Point abInters = getPoint(s);
        Point cdInters = SegmentLine(c,d).getPoint(t);

        // Si son paralelos
        if (!abInters.equal(cdInters))
        {
            std::cout << "Los puntos en cada segmento NO CONCUERDAN WTF" << std::endl;
            return nullptr;
        }

	    return new Point(abInters);
    }

Y luego para usarlos con cada tipo de recta usar ese método:

    virtual Point* intersectionPoint(const SegmentLine& segment);
    virtual Point* intersectionPoint(const RayLine& ray);
    virtual Point* intersectionPoint(const Line& line);

    {
        double s, t;
        Point* interseccion = intersectionPoint(segment._orig, segment._dest, s, t);

        // Esta dentro de ambos segmentos
        if (this->isTvalid(s) && segment.isTvalid(t))
            return interseccion;

        // En caso de que este contenido
        return nullptr; 
    }

Para las clases Line y RayLine he hecho lo mismo pero al irlos sobrecargando en estos subclases me he dado cuenta de que se puede dejar sin sobrecargar y el funcionamiento es el mismo, ya que el resultado depende de:

    (this.isTvalid(s) && segment.isTvalid(t))

## PRÁCTICA 2

### Planos

Los dibujo con transparencia y un contorno para que se distinga, con el modo de dibujo PLAIN y una luz ambiente con un alpha pequeño. Y el modo WIREFRAME para el contorno.

### Nube de puntos

Luego para el método getMostDistanced(a, b) lo he interpretado como los puntos de la nube cuya distancia entre ellos es la mayor, así que para encontrarlos habría que hacer un algoritmo O(n^2):

    double maxDistance = 0;
    
	for (int i = 0; i < _points.size(); i++)
	{
		for (int j = 0; j < _points.size(); j++)
		{
			const double d = (_points[i] - _points[j]).module();
			if (d > maxDistance)
			{
				a = i; b = j;
				maxDistance = d;
			}
		}
	}


He hecho además un algoritmo que calcula los puntos de máxima coordenada tal que:

    getMaxPoints(Vec3D& maxX, Vec3D& maxY, Vec3D& maxZ)
    {
        maxX.setX(-BasicGeom::BIGNUM);
        maxY.setY(-BasicGeom::BIGNUM);
        maxZ.setZ(-BasicGeom::BIGNUM);

        for (const Vec3D& point : _points)
        {
            if (point.getX() > maxX.getX())
                maxX = point;
            if (point.getY() > maxY.getY())
                maxY = point;
            if (point.getZ() > maxZ.getZ())
                maxZ = point;
        }
    }

Este sirve para los Modelos de triángulos más adelante

### Modelos de Triangulos

Para encontrar los triángulos de la malla más alejados en cada una de las coordenadas, he usado el método getMaxPoints(Vec3D& maxX, Vec3D& maxY, Vec3D& maxZ) de las Nubes de Puntos, ya que puedes convertir un Modelo en Nube de Puntos fácilmente.

1. Obtengo los puntos con el máximo y mínimo X, Y y Z.
2. Busco los triángulos de la malla que tiene este punto como uno de sus vértices
3. Los añado a listas separadas que comparten el punto por el que son buscados
4. Gracias al enum OrdenTriangulos puedo categorizar cada lista de triángulos por ser los de máxima X, Y,...
5. Itero cada lista con un color distinto (tengo una lista global con los 6 colores básicos para que sea más fácil)
6. Les aplico un desplazamiento hacia afuera sumándoles la normal a cada vértice para que no se superponga con el Modelo y se distingan
7. Los dibujo con su color respectivo

