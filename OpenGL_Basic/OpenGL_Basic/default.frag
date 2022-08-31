#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform vec3 cameraPosition;

void main()
{
	// outputs final color
	FragColor = texture(tex0, texCoord);
}