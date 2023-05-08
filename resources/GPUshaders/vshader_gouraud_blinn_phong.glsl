#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

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
    int type; // 0 for point, 1 for directional and 2 for spot

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

uniform mat4 model_view;
uniform mat4 projection;
uniform vec3 ambientGlobal;
uniform vec4 obs;
out vec4 color;

// The entry point for our vertex shader.
void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Different types of light:
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    vec3 globalAmbient = vec3(0.0);

    for (int i=0; i < 5; i++){ //array de lights de length 5
        Light light = light_info[i];
        // TODO attenuation
        float depthAttenuation = 1.0;

        //Calculate the ambient component
        lightAmbient += light.Ia * mat_info.Ka;

        //Calculate diffuse component
        vec3 L = vec3(0.0);
        if (light.type == 1){ // if directional...
            L = normalize(-light.direction);
        } else{
            vec3 lightPos = light.position;
            vec3 vertexPos = vec3(projection * model_view * vPosition);
            L = normalize(lightPos - vertexPos);
        }

        vec3 N = normalize(vNormal);
        float dotLN = dot(L, N);

        lightDiffuse += mat_info.Kd * light.Id * max(dotLN, 0.0f) * depthAttenuation;

        // Calculate the specular component
        vec3 fpos = vec3(projection * model_view * vPosition);
        vec3 V = normalize(obs - fpos);
        vec3 H = normalize(L + V);
        float dotNH = dot(N, H);
        lightSpecular += (mat_info.Ks * light.Is * pow(max(dotNH, 0.0f), mat_info.shininess)) * depthAttenuation;
    }

    // out color of the vertex
    color = vec4(lightAmbient + lightDiffuse + lightSpecular + globalAmbient, 1.0);
}
