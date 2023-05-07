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
uniform vec3 ambientGlobal; //vull veure esfera obtinguda amb aquest color
out vec4 color;

// The entry point for our vertex shader.
void main()
{
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
        vec3 N = vec3(0.0);
        float dotLN = dot(L, N);

        lightDiffuse += mat_info.Kd * light.Id * max(dotLN, 0.0f) * depthAttenuation;

        // Calculate the specular component
        vec3 V = vec3(0.0);
        vec3 H = vec3(0.0);
        float dotNH = dot(N, H);
        lightSpecular += (mat_info.Ks * light.Is * pow(max(dotNH, 0.0f), mat_info.shininess)) * depthAttenuation;
    }

    // out color of the vertex
    color = vec4(lightAmbient + lightDiffuse + lightSpecular + globalAmbient, 1.0);
}
