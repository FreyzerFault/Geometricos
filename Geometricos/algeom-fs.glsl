// FRAGMENT SHADER
#version 410

in salidaVS
{
   vec3 posicionV;
   vec3 normalV;
   vec2 cTexturaV;
} entrada;

//uniform vec4 materialIa;
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
vec4 colorMaterial ()
{
   return materialId;
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
vec4 colorMio ( vec4 colorDePartida )
{
   return ( micolor );
}



subroutine ( calcularColor )
vec4 luzAmbiente ( vec4 colorDePartida )
{
//   return materialIa * vec4 ( luzIa, 1 );
   return colorDePartida * vec4 ( luzIa, 1 );
}



subroutine ( calcularColor )
vec4 luzPuntual ( vec4 colorDePartida )
{
   vec3 n = normalize ( entrada.normalV );

   vec3 l = normalize ( luzPos - entrada.posicionV );
   vec3 v = normalize ( -entrada.posicionV );
   vec3 r = reflect ( -l, n );

//   vec4 colorD = vec4 ( luzId, 1 ) * materialId * max ( dot ( l, n ), 0 );
   vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
   vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
                 * pow ( max ( dot ( r, v ), 0 ), materialExp );

   return ( colorD + colorS );
}

subroutine ( calcularColor )
vec4 luzDireccional ( vec4 colorDePartida )
{
   vec3 n = normalize ( entrada.normalV );

   vec3 l = -luzDir;
   vec3 v = normalize ( -entrada.posicionV );
   vec3 r = reflect ( -l, n );

//   vec4 colorD = vec4 ( luzId, 1 ) * materialId * max ( dot ( l, n ), 0 );
   vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
   vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
                 * pow ( max ( dot ( r, v ), 0 ), materialExp );

   return ( colorD + colorS );
}

subroutine ( calcularColor )
vec4 luzFoco ( vec4 colorDePartida )
{
   vec3 l = normalize ( luzPos - entrada.posicionV );
   vec3 d = luzDir;
   float cosGamma = cos ( luzGamma );
   float factorSpot = 0;

   if ( dot ( -l, d ) >= cosGamma )
   {
      factorSpot = pow ( dot ( -l, d ), luzS );
   }

   vec3 n = normalize ( entrada.normalV );
   vec3 v = normalize ( -entrada.posicionV );
   vec3 r = reflect ( -l, n );

//   vec4 colorD = vec4 ( luzId, 1 ) * materialId * max ( dot ( l, n ), 0 );
   vec4 colorD = vec4 ( luzId, 1 ) * colorDePartida * max ( dot ( l, n ), 0 );
   vec4 colorS = vec4 ( luzIs, 1 ) * materialIs
                 * pow ( max ( dot ( r, v ), 0 ), materialExp );

   return factorSpot * ( colorD + colorS );
}

void main ()
{
   vec4 color = colorElegido ();
   colorFragmento = vec4 ( colorCalculado ( color ).rgb, 1 );
   
}