#version 330

in vec4 position;
in vec4 normal;
out vec4 colorOut;

struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float shininess;
    float opacity;
};

struct Light
{
    int type;
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

uniform Material mat_info;
uniform Light light_info[5];
uniform vec4 obs;

void main()
{
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    int numLights = light_info.length();
    vec4 L, N, H, V;
    V = normalize(obs - position);
    for(int i = 0; i < numLights; i++){
        //Calculate the ambient component
        lightAmbient += light_info[i].Ia * mat_info.Ka;

        //Calculate the diffuse component
        L = normalize(vec4(light_info[i].position, 1.0) - position); //normalized
        N = normalize(normal);
        lightDiffuse += light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

        //Calculate the specular component

        H = normalize(L + V); // Half vector
        lightSpecular += mat_info.Ks * light_info[i].Is * pow(max(dot(N, H), 0.0f), mat_info.shininess);
    }
    colorOut = vec4(lightAmbient + lightDiffuse + lightSpecular, mat_info.opacity);
}
