#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 cameraProjectionMatrix;
uniform mat4 cameraViewMatrix;
uniform mat4 cameraModelMatrix;

out vec3 outColor;

void main()
{
    gl_Position = cameraProjectionMatrix  * cameraViewMatrix* cameraModelMatrix * vec4(aPos, 1.0);
    outColor = aColor;
}