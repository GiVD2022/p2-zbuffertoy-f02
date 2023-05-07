#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

struct Light
{
    vec3 Ia;
    vec3 Id;
    vec3 Is;

    // Directional lights
    vec3 direction;
    float intensity;

    // spot lights
    vec3 spotDirection;
    float spotCosineCutoff;
    float spotExponent;

    // point lights
    vec3 position;
    vec3 coeficients;
};

struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float shininess;
    float opacity;
};

uniform Material mat_info;  // a la memòria central de la GPU

uniform Light light_info[5];    //array de 5 elements. Aquest valor sempre ha de ser un numero

uniform mat4 model_view;
uniform mat4 projection;
uniform vec3 ambientGlobal; //vull veure esfera obtinguda amb aquest color
out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    color = vec4(light_info[0].Is, 1.0f); //agafa tres components de l'ambient global, la quarta es la opacitat

    //Testeig de direccionals
    color = vec4(light_info[0].Ia, 1.0f);

}
