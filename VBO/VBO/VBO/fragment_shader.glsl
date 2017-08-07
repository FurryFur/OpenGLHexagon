#version 420 core

//in vec4 outPosition;
in vec3 outColor;

void main(void)
{
    gl_FragColor = vec4(outColor, 1.0);
}
