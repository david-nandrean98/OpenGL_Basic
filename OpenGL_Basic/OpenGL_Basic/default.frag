#version 330 core

struct Light
{
	int type;
	vec3 color;
	vec3 position;
};

uniform Light lights[5];

uniform int light_num;

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the texture coordinates from the Vertex Shader
in vec3 crntPos;
in vec3 Normal;
in vec3 Color;
in vec2 texCoord;
// Imports the normal from the Vertex Shader
// Imports the current position from the Vertex Shader

// Gets the Texture Unit from the main function
uniform vec3 cameraPosition;
uniform sampler2D tex0;



vec3 applyLights()
{

	vec3 result = vec3(0.0f);
	vec3 viewDir = normalize(cameraPosition - crntPos);
	//if(dot(Normal, viewDir) < 0) return vec3(0.0f);
	for(int i = 0; i < light_num; i++)
	{
		if (lights[i].type == 0)
		{
			vec3 reflection = reflect(lights[i].position, Normal);
			vec3 halfwayDir = normalize(lights[i].position + viewDir);
			result += (0.1f + max(0.0, dot(Normal, lights[i].position)) + pow(max(dot(Normal, halfwayDir), 0.0), 16.0f)) * lights[i].color;
		}
	}
	return result;
}


void main()
{
	// outputs final color
	FragColor = vec4(applyLights(), 1.0f);
}