#version 330

// Input vertex data
in vec4 position;   // vertex position
in vec4 normal;     // vertex normal
in vec2 v_texcoord;

// Output data for the fragment shader
out vec4 colorOut;

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

// Uniform variables (same for all vertices)
uniform Material mat_info;  // a la memòria central de la GPU
uniform Light light_info[5];    //array de 5 elements. Aquest valor sempre ha de ser un numero
uniform vec4 obs;          // camera position
uniform vec3 ambientGlobal;

uniform sampler2D texMap;

// Main function (called once per vertex)
void main()
{
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    int numLights = light_info.length();
    vec4 L, N, R, V;
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
            R = normalize( 2.0 * (dot(N, L) * N) - L);
            V = normalize(obs - position);
            lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * pow(max(dot(R,V), 0.0f), mat_info.shininess);

        } else if(light_info[i].type == 1){ //spot light
            //Calculate the diffuse component
            L = vec4(light_info[i].position, 1.0) - position;
            N = normalize(normal);
            distance = length(vec3(L));
            L = normalize(L); //normalized
            attenuation = max(min(1./(light_info[i].coeficients.z + light_info[i].coeficients.y * distance + light_info[i].coeficients.x * distance * distance),1.),0.);
            spotEffect = dot(-L, normalize(vec4(light_info[i].spotDirection, 0.0)));
            if (spotEffect > light_info[i].spotCosineCutoff) { //surface point is inside the cone of the spot light
                spotEffect = pow(spotEffect, light_info[i].spotExponent);
                lightDiffuse += attenuation * light_info[i].Id * mat_info.Kd * spotEffect * max(dot(L, N), 0.0);

                //Calculate the specular component
                R = normalize( 2.0 * (dot(N, L) * N) - L);
                V = normalize(obs - position);
                lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * spotEffect * pow(max(dot(R,V), 0.0f), mat_info.shininess);
            }

        } else if (light_info[i].type == 2){ //directional light
            //Calculate the diffuse component
            L = -normalize(vec4(light_info[i].direction, 0.0)); //normalized
            lightDiffuse += light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

            //Calculate the specular component
            R = normalize( 2.0 * (dot(N, L) * N) - L);
            V = normalize(obs - position);
            lightSpecular += mat_info.Ks * light_info[i].Is * pow(max(dot(R,V), 0.0f), mat_info.shininess);
        }

    }
    vec3 newDiffuse = 0.25 * lightDiffuse + 0.75 * vec3(texture(texMap, v_texcoord).rgb);
    colorOut = vec4(ambientGlobal * mat_info.Ka + lightAmbient + newDiffuse + lightSpecular, mat_info.opacity);
}

