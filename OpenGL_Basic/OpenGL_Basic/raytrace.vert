#version 330 core
layout (location = 0) in vec2 inPos;

out vec3 rayDir;
out vec3 eyePos;

uniform mat4 rayDirMatrix;
uniform vec3 cameraPos;

void main()
{
    vec4 pos = vec4(inPos, 0.0f, 1.0f);
    // Calculating the direction of the ray
    rayDir = (rayDirMatrix * pos).xyz - cameraPos;
    eyePos = cameraPos;
    gl_Position = pos;
}