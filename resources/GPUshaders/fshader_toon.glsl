#version 330

in vec4 position;
in vec4 normal;
in float alpha;
flat in int numLights;
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


uniform Material mat_info;

void main(void)
{
    vec3 toonLight = vec3(0.0);
    for(int i = 0; i < numLights; i++){
        if (alpha > 0.75){
            toonLight+= mat_info.Kd;
        }
        if(alpha < 0.75 && alpha > 0.5){
            toonLight+= mat_info.Kd*0.75;
        }
        if(alpha < 0.5 && alpha > 0.25){
            toonLight+= mat_info.Kd*0.5;
        }
        if(alpha < 0.25 ){
            toonLight+= mat_info.Kd*0.25;
        }

    }
    colorOut = vec4(toonLight,1.0);
}
