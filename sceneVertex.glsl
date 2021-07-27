#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;

uniform mat4 cameraProjectionMatrix;
uniform mat4 cameraViewMatrix;
uniform mat4 cameraModelMatrix;

uniform mat4 lightProjectionMatrix;
uniform mat4 lightViewMatrix;

out VS_OUT {
    vec4 vEyeSpacePosVertex;
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec4 FragProjection;
} vs_out;

void main()
{
    vs_out.vEyeSpacePosVertex = cameraModelMatrix * cameraViewMatrix * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(cameraModelMatrix * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(cameraModelMatrix))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightProjectionMatrix * lightViewMatrix * vec4(vs_out.FragPos, 1.0);

    vs_out.FragProjection = cameraProjectionMatrix * cameraViewMatrix * cameraModelMatrix * vec4(vs_out.FragPos, 1.0);


    gl_Position = cameraProjectionMatrix * cameraViewMatrix * cameraModelMatrix * vec4(aPos, 1.0);
}