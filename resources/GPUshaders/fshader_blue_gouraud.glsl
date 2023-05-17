#version 330

in vec3 lightAmbientO;
in vec3 lightDiffuseO;
in vec3 lightSpecularO;
in vec3 globalAmbientO;
in float opacityO;
in vec2 v_texcoord;

out vec4 colorOut;

uniform sampler2D texMap;

uniform bool hasTexture;

void main()
{
    //colorOut = color;
    vec3 newDiffuse;
    if(hasTexture){
        newDiffuse = 0.5 * lightDiffuseO + 0.5 * vec3(texture(texMap, v_texcoord).rgb);
    }else{
        newDiffuse = lightDiffuseO;
    }
    colorOut = vec4( lightAmbientO + newDiffuse + lightSpecularO + globalAmbientO, opacityO);

    //colorOut = vec4(v_texcoord.x, v_texcoord.y, 0.f,1.f);
}

