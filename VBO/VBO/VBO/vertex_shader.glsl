#version 420 core

//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;

in vec3 position;
// in vec3 color;
uniform float currentTime;

out vec4 outPosition;

void main() {
    mat4 R = mat4(
        cos(currentTime), sin(currentTime), 0.0, 0.0,
        -sin(currentTime), cos(currentTime), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    outPosition = R * vec4(position, 1.0);
    gl_Position = outPosition;
    outPosition = R * outPosition; // Make color rotation faster
}