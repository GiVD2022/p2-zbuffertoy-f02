#version 330

// Input vertex data
in vec4 position;   // vertex position
in vec4 normal;     // vertex normal
in vec2 v_texcoord;

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


uniform sampler2D texMap;
uniform bool hasTexture;

uniform vec4 obs;          // camera position
uniform vec3 ambientGlobal;
uniform vec2 viewportSize;
uniform float radi;

void main()
{
    // Check if pixel is inside the night vision circle
    vec2 pixelCoord = gl_FragCoord.xy;
    vec2 center = viewportSize / 2.0f;
    float dist = length(pixelCoord - center);

    if (dist > radi){
        colorOut = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return; // Early termination
    }

    vec4 candidate_color;
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);


    vec4 L, N, R, V;
    float spotEffect, attenuation, distance;

    // Precalculate N (normal) and V (view direction) outside the loop
    N = normalize(normal);
    V = normalize(obs - position);

    int numLights = light_info.length();

    for(int i = 0; i < numLights; i++){

        // Calculate the ambient component (same for all light types)
        lightAmbient += light_info[i].Ia * mat_info.Ka;

        if(light_info[i].type == 0){ //point light

            //Calculate the diffuse component
            L = vec4(light_info[i].position, 1.0) - position;
            distance = length(vec3(L));
            L = normalize(L); //normalized
            attenuation = max(min(1./(light_info[i].coeficients.z + light_info[i].coeficients.y * distance + light_info[i].coeficients.x * distance * distance),1.),0.);
            lightDiffuse += attenuation * light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

            //Calculate the specular component
            R = normalize( 2.0 * (dot(N, L) * N) - L);
            lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * pow(max(dot(R,V), 0.0f), mat_info.shininess);

        } else if(light_info[i].type == 1){ //spot light

            //Calculate the diffuse component
            L = vec4(light_info[i].position, 1.0) - position;
            distance = length(vec3(L));
            L = normalize(L); //normalized
            attenuation = max(min(1./(light_info[i].coeficients.z + light_info[i].coeficients.y * distance + light_info[i].coeficients.x * distance * distance),1.),0.);
            spotEffect = dot(-L, normalize(vec4(light_info[i].spotDirection, 0.0)));

            if (spotEffect > light_info[i].spotCosineCutoff) { //surface point is inside the cone of the spot light
                spotEffect = pow(spotEffect, light_info[i].spotExponent);
                lightDiffuse += attenuation * light_info[i].Id * mat_info.Kd * spotEffect * max(dot(L, N), 0.0);

                //Calculate the specular component
                R = normalize( 2.0 * (dot(N, L) * N) - L);
                lightSpecular += attenuation * mat_info.Ks * light_info[i].Is * spotEffect * pow(max(dot(R,V), 0.0f), mat_info.shininess);
            }

        } else if (light_info[i].type == 2){ //directional light

            //Calculate the diffuse component
            L = -normalize(vec4(light_info[i].direction, 0.0)); //normalized
            lightDiffuse += light_info[i].Id * mat_info.Kd * max(dot(L, N), 0.0);

            //Calculate the specular component
            R = normalize( 2.0 * (dot(N, L) * N) - L);
            lightSpecular += mat_info.Ks * light_info[i].Is * pow(max(dot(R,V), 0.0f), mat_info.shininess);
        }

    }

    vec3 newDiffuse;

    if(hasTexture){
        newDiffuse = 0.25 * lightDiffuse + 0.75 * vec3(texture(texMap, v_texcoord).rgb);
    }else{
        newDiffuse = lightDiffuse;
    }
    candidate_color = vec4(ambientGlobal * mat_info.Ka + lightAmbient + newDiffuse + lightSpecular, mat_info.opacity);
    float color_green = sqrt(candidate_color.r*candidate_color.r + candidate_color.g*candidate_color.g + candidate_color.b*candidate_color.b)/3.0;
    colorOut = vec4(0.0f, color_green, 0.0f, mat_info.opacity);
}

