#version 330

in vec4 color;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;
uniform bool hasTexture;

uniform vec4 obs;          // camera position
uniform vec2 viewportSize;
uniform float radi;

void main()
{
    // Check if pixel is inside the night vision circle
    vec2 pixelCoord = gl_FragCoord.xy;
    vec2 center = viewportSize / 2.0f;
    float dist = length(pixelCoord - center);
    if(dist > radi){
        colorOut = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }else{
        if(hasTexture){
            colorOut = 0.25 * color + 0.75 * vec4(texture(texMap, v_texcoord).rgb, 1.0f);
        }else{
            colorOut = color;
        }
    }
}

