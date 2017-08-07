#version 420 core

in vec4 outPosition;
// in vec3 outColor;
// uniform float currentTime;

void main(void)
{
    gl_FragColor = vec4((sin(outPosition.x * 3.14) + 1) / 2, (cos(outPosition.y * 3.14) + 1) / 2, 0.5, 1.0);
}
