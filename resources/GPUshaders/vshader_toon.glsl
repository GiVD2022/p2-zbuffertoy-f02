#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 model_view;
uniform mat4 projection;

struct Light
{
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    int type; // 0 point, 1 spot, 2 directional

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


out vec4 position;
out vec4 normal;
out float alpha;
flat out int numLights;

uniform Light light_info[5];
uniform vec4 obs;

void main(void)
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    position = vPosition;
    normal = vNormal;
    numLights = 1; //We have actualy one light, and that's why we pass the alpha as a single value
    vec4 L, N, H, V;
    V = normalize(obs - vPosition);
    //Calculate the diffuspositione component
    L = normalize(vec4(light_info[0].position, 1.0) - vPosition); //normalized
    N = normalize(normal);
    alpha= max(dot(N, L), 0.0f);


}
