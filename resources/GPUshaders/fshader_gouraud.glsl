#version 330

in vec3 lightAmbientO;
in vec3 lightDiffuseO;
in vec3 lightSpecularO;
in vec3 globalAmbientO;
in float opacityO;
in vec2 v_texcoord;

out vec4 colorOut;

uniform sampler2D texMap;

void main()
{
    //colorOut = color;
    vec3 newDiffuse = 0.25 * lightDiffuseO + 0.75 * vec3(texture(texMap, v_texcoord).rgb);
    colorOut = vec4( lightAmbientO + newDiffuse + lightSpecularO + globalAmbientO, opacityO);

    //colorOut = vec4(v_texcoord.x, v_texcoord.y, 0.f,1.f);
}

