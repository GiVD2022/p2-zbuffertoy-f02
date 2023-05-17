#version 330
// Common
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;
uniform bool hasTexture;


// Goraud
in vec3 lightAmbientO;
in vec3 lightDiffuseO;
in vec3 lightSpecularO;
in vec3 globalAmbientO;
in float opacityO;

// Blinn phong

/*
in vec4 position;   // vertex position
in vec4 normal;     // vertex normal
// Material properties
struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float shininess;
    float opacity;
};

// Light properties
struct Light
{
    int type;   // 0=point light, 1=spotlight, 2=directional light
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
uniform Material mat_info;  // a la memòria central de la GPU
uniform Light light_info[5];    //array de 5 elements. Aquest valor sempre ha de ser un numero
uniform vec4 obs;          // camera position
uniform vec3 ambientGlobal;
*/

void main()
{
    //colorOut = color;
    vec3 newDiffuse;
    if(hasTexture){
        newDiffuse = 0.5 * lightDiffuseO + 0.5 * vec3(texture(texMap, v_texcoord).rgb);
    }else{
        newDiffuse = lightDiffuseO;
    }
    colorOut = vec4( lightAmbientO + newDiffuse + lightSpecularO + globalAmbientO, opacityO);

    //colorOut = vec4(v_texcoord.x, v_texcoord.y, 0.f,1.f);
}

