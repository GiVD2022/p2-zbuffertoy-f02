#version 330

in vec4 color;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;
uniform bool hasTexture;

void main()
{
    //colorOut = color;
    if(hasTexture){// 0.25 * color + 0.75 *
        colorOut = vec4(texture(texMap, v_texcoord).rgb, 1.0f);
    }else{
        colorOut = color;
    }
    //colorOut = vec4(v_texcoord.x, v_texcoord.y, 0.0, 1.0);
}

