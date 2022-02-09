// VERTEX SHADER
#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 cTextura;

uniform mat4 matrizMVP;
uniform mat4 matrizMV;
uniform mat4 matrizMVit;

out salidaVS
{
   vec3 posicionV;
   vec3 normalV;
   vec2 cTexturaV;
} salida;

void main ()
{
   salida.posicionV = vec3 ( matrizMV * vec4 ( posicion, 1 ) );
   salida.normalV = vec3 ( matrizMVit * vec4 ( normal, 0 ) );
   salida.cTexturaV = cTextura;
   gl_Position = matrizMVP * vec4 ( posicion, 1 );
}