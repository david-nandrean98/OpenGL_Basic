#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;

// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;

uniform mat4 cameraMatrix;
uniform mat4 model;


void main()
{
	crntPos = vec3(model * vec4(aPosition, 1.0f));
	gl_Position = cameraMatrix * vec4(crntPos, 1.0);

	texCoord = aTexture;
	Normal = aNormal;
}