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
    vec3 Ia;
    vec3 Id;
    vec3 Is;

    // point lights
    vec3 position;
    vec3 coeficients;
    // Directional lights
    vec3 direction;
    float intensity;

    // spot lights
    vec3 spotDirection;
    float spotCosineCutoff;
    float spotExponent;


};

uniform Material mat_info;
uniform Light light_info[5];
uniform vec4 obs;

void main(void)
{
    vec3 toonLight = vec3(0.0);
    int numLights = light_info.length();
    vec4 L, N, H, V;
    int n,j;
    float rimDot,alpha;
    V = normalize(obs - position);
    for(int i = 0; i < 1; i++){

        //Calculate the diffuspositione component
        L = normalize(vec4(light_info[i].position, 1.0) - position); //normalized
        N = normalize(normal);
        alpha = max(dot(N, L), 0.0f);

        H = normalize(L + V); // Half vector

        //Calculate the toon component
        n = 10;
        j = min(int(floor(n * alpha)), n-1);


        if (alpha > 0.75){
            toonLight= mat_info.Kd;
        }
        if(alpha < 0.75 && alpha > 0.5){
            toonLight= mat_info.Kd*0.75;
        }
        if(alpha < 0.5 && alpha > 0.25){
            toonLight= mat_info.Kd*0.5;
        }
        if(alpha < 0.25 ){
            toonLight= mat_info.Kd*0.25;
        }

    }
    colorOut = vec4(toonLight,1.0);
}
