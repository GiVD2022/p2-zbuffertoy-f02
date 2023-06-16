#version 330

out vec4 FragColor;

void main()
{
    float depth = gl_FragCoord.z;
    // Convert depth value to gray scale between 0 and 1
    float gray = (depth - 0.1) / (0.9 - 0.1); // adjust clipping planes here

    // Clamp gray value to between 0 and 1
    gray = clamp(gray, 0.0, 1.0);

    FragColor = vec4(vec3(gray), 1.0f);
}

