#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 0) in vec2 tex;
layout (location = 0) in vec3 color;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightProjectionMatrix  * lightViewMatrix* model * vec4(aPos, 1.0);
}