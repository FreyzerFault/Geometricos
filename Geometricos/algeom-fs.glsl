// FRAGMENT SHADER
#version 410

in salidaVS
{
   vec3 posicionV;
   vec3 normalV;
   vec2 cTexturaV;
} entrada;

uniform vec4 materialIa;
uniform vec4 materialId;
uniform vec4 materialIs;
uniform float materialExp;
uniform vec3 luzIa;
uniform vec3 luzId;
uniform vec3 luzIs;
uniform vec3 luzPos;
uniform vec3 luzDir;
uniform float luzGamma;
uniform float luzS;

//mio
uniform vec4 micolor;

uniform sampler2D muestreador;

out vec4 colorFragmento;

///////////////////////////////////////////////////////////////////
// Subrutina para elegir el color entre el material y la textura //
///////////////////////////////////////////////////////////////////
subroutine vec4 elegirColor ();
subroutine uniform elegirColor colorElegido;

subroutine ( elegirColor )
vec4 colorTextura ()
{
   return texture ( muestreador, entrada.cTexturaV );
}

subroutine ( elegirColor )
vec4 colorBasico ()
{
   return micolor;
}

subroutine ( elegirColor )
vec4 colorMaterial ()
{
   return materialId;
}

subroutine ( elegirColor )
vec4 colorAmbiente ()
{
   return materialIa;
}


///////////////////////////////////////////////////
// Subrutina para calcular el color según la luz //
///////////////////////////////////////////////////
subroutine vec4 calcularColor ( vec4 colorDePartida );
subroutine uniform calcularColor colorCalculado;

subroutine ( calcularColor )
vec4 colorAlambre ( vec4 colorDePartida )
{
   return ( vec4 ( 1, 0, 1, 1 ) );
}

subroutine ( calcularColor )
vec4 unlit ( vec4 colorDePartida )
{
   return colorDePartida;
}



subroutine ( calcularColor )
vec4 luzAmbiente ( vec4 colorDePartida )
{
	return colorDePartida * vec4 ( luzIa, 1 );
}


subroutine ( calcularColor )
vec4 luzPuntual ( vec4 colorDePartida )
{
	vec3 n = normalize ( entrada.normalV );
	
	if (!gl_FrontFacing)
		n = -n;

	vec3 l = normalize ( luzPos - entrada.posicionV );
	vec3 v = normalize ( -entrada.posicionV );
	vec3 r = reflect ( -l, n );
	
	// Checkea si el angulo entre camDir y lightDir es menor a 90
	// No hay luz specular si el angulo es mayor a 90
	// Cuando se implementen las sombras no hara falta.
	float specFactor = step(0, dot(n,v));

	vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
	vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
				  * pow ( max ( dot ( r, v ), 0 ), materialExp )
				  * specFactor;

	return vec4( colorD.rgb + colorS.rgb, colorD.a );
}

subroutine ( calcularColor )
vec4 luzDireccional ( vec4 colorDePartida )
{
	vec3 n = normalize ( entrada.normalV );
	
	if (!gl_FrontFacing)
		n = -n;
	
	vec3 l = -luzDir;
	vec3 v = normalize ( -entrada.posicionV );
	vec3 r = reflect ( -l, n );
	
	float specFactor = step(0, dot(n,v));
	
	vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
	vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
				 * pow ( max ( dot ( r, v ), 0 ), materialExp )
				 * specFactor;

	return vec4( colorD.rgb + colorS.rgb, colorD.a );
}

subroutine ( calcularColor )
vec4 luzFoco ( vec4 colorDePartida )
{
	vec3 l = normalize ( luzPos - entrada.posicionV );
	vec3 d = luzDir;

	// Coseno del angulo de apertura del foco
	
	float PI = 3.141592653589793;
	float cosGamma = cos(luzGamma * PI / 180.);
	float cosDelta = dot(-l, d);

	// Usando el Exponente de atenuacion angular que a mas grande más concentrada esta
	float spotFactor;
	
	
	// Smoothstep es una funcion similar al 0.5 * cos + 0.5, va de 0 a 1, de borde a centro
	// Esto hace que la concentracion de la luz sea proporcional al angulo del foco dado por cosGamma y no al maximo angulo de 90º
	// Asi evita bordes duros en el foco si el spotExp es bajo
	// Ademas no haria falta el primer step()
	//spotFactor = smoothstep(cosGamma, 1, cosDelta);

	// Step = if (cosDelta < cosGamma) { spotFactor = 0.0; } 
	// Si está fuera del rango del foco es 0, sino 1
	spotFactor = step(cosGamma, cosDelta);

	// Esto haria innecesario usar spotExp, ya que se podria crear el mismo efecto cambiando el radio del foco
	

	// Concentra la luz en el centro a más grande es spotExp
	spotFactor *= pow(cosDelta, luzS);
	
	vec3 n = normalize ( entrada.normalV );
	
	if (!gl_FrontFacing)
		n = -n;
	
	vec3 v = normalize ( -entrada.posicionV );
	vec3 r = reflect ( -l, n );
	
	float specFactor = step(0, dot(n,v));
	
	vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
	vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
				 * pow ( max ( dot ( r, v ), 0 ), materialExp )
				 * specFactor;
	
	return spotFactor * vec4( colorD.rgb + colorS.rgb, colorD.a );
}

void main ()
{
   vec4 color = colorElegido ();
   colorFragmento = vec4 ( colorCalculado ( color ).rgba );
   
}