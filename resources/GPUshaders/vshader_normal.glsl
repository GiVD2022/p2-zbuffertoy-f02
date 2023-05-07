#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

out vec4 color;

void main()
{
    //Testeig de direccionals
    color = vNormal;
}
