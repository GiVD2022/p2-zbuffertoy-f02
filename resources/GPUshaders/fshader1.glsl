#version 330

in vec4 color;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;

void main()
{
    //colorOut = color;
    colorOut = 0.25 * color + 0.75 * vec4(texture(texMap, v_texcoord).rgb, 1.0f);

    //colorOut = vec4(v_texcoord.x, v_texcoord.y, 0.f,1.f);
}

