#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float shininess;
    float opacity;
};

uniform Material mat_info;  // a la memòria central de la GPU

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    color = vec4(mat_info.Kd, 1.0f);
}
