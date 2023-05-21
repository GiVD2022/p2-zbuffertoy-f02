#version 330
// Common
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;
uniform bool hasTexture;

uniform float stormRadius;


// Goraud
in vec3 lightAmbientO;
in vec3 lightDiffuseO;
in vec3 lightSpecularO;
in vec3 globalAmbientO;
in float opacityO;

// Blinn phong
in vec4 position;   // vertex position
in vec4 normal;     // vertex normal

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
uniform vec4 obs;          // camera position
uniform vec3 ambientGlobal;


void main()
{

    if (pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2) > pow(stormRadius, 2)) {

        vec3 lightAmbient = vec3(0.0);
        vec3 lightDiffuse = vec3(0.0);
        vec3 lightSpecular = vec3(0.0);
        int numLights = light_info.length();
        vec4 L, N, H;
        float spotEffect, attenuation, distance;
        for(int i = 0; i < numLights; i++){
            // Calculate the ambient component (same for all light types)
            lightAmbient += light_info[i].Ia * mat_info.Ka;
            if(light_info[i].type == 0){ //point light
                //Calculate the diffuse component
                L = vec4(light_info[i].position, 1.0) - position;
                N = normalize(normal);
                distance = length(vec3(L));
                L = normalize(L); //normalized
                attenuation = max(min(1./(light_info[i].coeficients.z + light_info[i].coeficients.y * distance + light_info[i].coeficients.x * distance * distance),1.),0.);
                lightDiffuse += attenuation * light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

                //Calculate the specular component
                H = normalize(L + normalize(obs - position));
                lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * pow(max(dot(N, H), 0.0f), mat_info.shininess);

            } else if(light_info[i].type == 1){ //spot light
                //Calculate the diffuse component
                L = vec4(light_info[i].position, 1.0) - position;
                N = normalize(normal);
                distance = length(vec3(L));
                L = normalize(L);//normalized
                attenuation = max(min(1./(light_info[i].coeficients.z + light_info[i].coeficients.y * distance + light_info[i].coeficients.x * distance * distance),1.),0.);
                spotEffect = dot(-L, normalize(vec4(light_info[i].spotDirection, 0.0)));
                if (spotEffect > light_info[i].spotCosineCutoff) { //surface point is inside the cone of the spot light
                    spotEffect = pow(spotEffect, light_info[i].spotExponent);
                    lightDiffuse += attenuation * light_info[i].Id * mat_info.Kd * spotEffect * max(dot(L, N), 0.0);

                    //Calculate the specular component
                    H = normalize(L + normalize(obs - position));
                    lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * spotEffect * pow(max(dot(N, H), 0.0f), mat_info.shininess);
                }

            } else if (light_info[i].type == 2){ //directional light
                //Calculate the diffuse component
                L = -normalize(vec4(light_info[i].direction, 0.0)); //normalized
                lightDiffuse += light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

                //Calculate the specular component
                H = normalize(L + normalize(obs - position));
                lightSpecular += mat_info.Ks * light_info[i].Is * pow(max(dot(N, H), 0.0f), mat_info.shininess);
            }
        }
        vec3 newDiffuse;
        if(hasTexture){
            newDiffuse = 0.25 * lightDiffuse + 0.75 * vec3(texture(texMap, v_texcoord).rgb);
        }else{
            newDiffuse = lightDiffuse;
        }
        colorOut = vec4(ambientGlobal * mat_info.Ka + lightAmbient + newDiffuse + lightSpecular, mat_info.opacity);

    } else {
        vec3 newDiffuse;
        if(hasTexture){
            newDiffuse = 0.25 * lightDiffuseO + 0.75 * vec3(texture(texMap, v_texcoord).rgb);
        }else{
            newDiffuse = lightDiffuseO;
        }
        colorOut = vec4( lightAmbientO + newDiffuse + lightSpecularO + globalAmbientO, opacityO);
    }
}

