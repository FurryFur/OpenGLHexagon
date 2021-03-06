#version 420 core

//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;

in vec3 position;
// in vec3 color;
uniform float currentTime;

out vec3 outColor;

const float PI = 3.14;
const float speed = 5.0;
const float offset = 2.0 * PI / 3.0;

void main() {
    float theta = atan(position.y, position.x);

    theta += speed * currentTime;
    outColor.r = (cos(theta) + 1.0) / 2.0;
    outColor.b = (cos(theta + offset) + 1.0) / 2.0;
    outColor.g = (cos(theta + 2.0 * offset) + 1.0) / 2.0;

    mat4 R = mat4(
        cos(currentTime), sin(currentTime), 0.0, 0.0,
        -sin(currentTime), cos(currentTime), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    gl_Position = R * vec4(position, 1.0);
}