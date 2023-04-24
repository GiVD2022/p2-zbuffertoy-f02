#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 model_view;
uniform mat4 projection;
uniform vec3 ambientGlobal; //vull veure esfera obtinguda amb aquest color
struct Light
{
vec3 Ia;
vec3 Id;
float Is;
};
uniform Light conjunt[5];
out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    color = vec4(ambientGlobal.xyz, 1.0f); //agafa tres components de l'ambient global, la quarta es la opacitat
}
