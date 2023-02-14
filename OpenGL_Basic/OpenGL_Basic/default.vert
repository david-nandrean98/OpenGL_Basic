#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

out vec3 Color;
out vec2 texCoord;

uniform mat4 cameraMatrix;
uniform mat4 model;



void main()
{
	crntPos = (model * vec4(aPosition, 1.0f)).xyz;
	Color = aColor;
	Normal = aNormal;
	texCoord = aTex;
	gl_Position = cameraMatrix * vec4(crntPos, 1.0);
}