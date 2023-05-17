#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;
layout (location = 2) in vec2 vTexture;

// Common
out vec2 v_texcoord;
uniform mat4 model_view;
uniform mat4 projection;
uniform float stormRadius;

// Goraud
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
    vec3 Ia;
    vec3 Id;
    vec3 Is;
    int type; // 0 for point, 1 for spot and 2 for direction

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

uniform Material mat_info;  // a la memòria central de la GPU
uniform Light light_info[5];    //array de 5 elements. Aquest valor sempre ha de ser un numero


uniform vec3 ambientGlobal;
uniform vec4 obs;

out vec3 lightAmbientO;
out vec3 lightDiffuseO;
out vec3 lightSpecularO;
out vec3 globalAmbientO;
out float opacityO;

// Blinn phong

out vec4 position;
out vec4 normal;


// The entry point for our vertex shader.
void main()
{

    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Different types of light:
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    vec3 globalAmbient = ambientGlobal * mat_info.Ka;

    float R = 0.7;

    int numLights = light_info.length();

    vec4 L, N, H;
    float spotEffect, attenuation, distance;

    if(pow(vPosition.x, 2) + pow(vPosition.y, 2) + pow(vPosition.z, 2) < pow(R, 2)){

        for (int i=0; i < numLights; i++){ //array de lights de length 5
            Light light = light_info[i];
            lightAmbient += light.Ia * mat_info.Ka;
            if (light.type == 0) // point light
            {
                // Diffuse component
                L = vec4(light.position, 1.0) - vPosition;
                N = normalize(vNormal);
                distance = length(vec3(L));
                L = normalize(L);
                attenuation = max(min(1.0 / (light.coeficients.z + light.coeficients.y * distance + light.coeficients.x * distance * distance), 1.0), 0.0);
                lightDiffuse += attenuation * light.Id * mat_info.Kd * max(dot(L, N), 0.0);

                // Specular
                H = normalize(L + normalize(obs - vPosition));
                lightSpecular += attenuation * mat_info.Ks * light.Is * pow(max(dot(N, H), 0.0f), mat_info.shininess);

            }
            else if (light.type == 1) // spot light
            {
                //Calculate the diffuse component
                L = vec4(light.position, 1.0) - vPosition;
                N = normalize(vNormal);
                distance = length(vec3(L));
                L = normalize(L);
                attenuation = max(min(1.0 / (light.coeficients.z + light.coeficients.y * distance + light.coeficients.x * distance * distance), 1.0), 0.0);
                spotEffect = dot(-L, normalize(vec4(light.spotDirection, 0.0)));
                if (spotEffect > light.spotCosineCutoff) { //surface point is inside the cone of the spot light
                    spotEffect = pow(spotEffect, light.spotExponent);
                    lightDiffuse += attenuation * light.Id * mat_info.Kd * spotEffect * max(dot(L, N), 0.0);

                    //Calculate the specular component
                    H = normalize(L + normalize(obs - vPosition));
                    lightSpecular += attenuation * mat_info.Ks * light.Is * spotEffect * pow(max(dot(N, H), 0.0f), mat_info.shininess);
                }

            }
            else if (light.type == 2) //directional light
            {
                //diffuse
                L = -normalize(vec4(light.direction, 0.0));
                lightDiffuse += light.Id * mat_info.Kd * max(dot(L, N), 0.0);

                //specular
                H = normalize(L + normalize(obs - vPosition));
                lightSpecular += mat_info.Ks * light.Is * pow(max(dot(N, H), 0.0f), mat_info.shininess);
            }
        }
        lightDiffuse.z = 1;
    }

    // Gouraud
    lightAmbientO = lightAmbient;
    lightDiffuseO = lightDiffuse;
    lightSpecularO = lightSpecular;
    globalAmbientO = globalAmbient;
    opacityO = mat_info.opacity;

    // Common
    v_texcoord = vTexture;

    // Blinn phong
    position = vPosition;
    normal = vNormal;
}
