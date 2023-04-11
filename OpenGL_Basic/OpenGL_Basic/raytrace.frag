#version 330 core
out vec4 FragColor;

in vec3 rayDir;
in vec3 eyePos;

uniform samplerCube skybox;


struct Light
{
	int type;
	vec3 color;
	vec3 position;
};

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct SceneSurface
{
    mat4 surface;
    Material material;
    int type;
};

uniform SceneSurface surfaces[25];
uniform Light lights[10];
uniform int surfaces_num;
uniform int lights_num;

float intersectQuadric(vec4 e, vec4 d, mat4 surface)
{
  float a = dot(d * surface, d);
  float b = dot(d * surface, e) + dot(e * surface, d);
  float c = dot(e * surface, e);

  float delta = b * b - 4.0 * a * c;
  if(delta < 0.0){
    return -1.0;
  }
  float delta_sqrt = sqrt(delta);
  float t1 = (-b - delta_sqrt) / (2.0 * a);
  float t2 = (-b + delta_sqrt) / (2.0 * a);  


  if (t1 < 0.0) return t2;
  else if (t2 < 0.0) return t1;
  else return min(t1, t2);
}


float findClosestSurface(vec4 eye, vec4 dir, out int idx)
{
    float t = 99999.0f; 
    for (int i = 0; i < surfaces_num; i++)
    {
        float t_hit = intersectQuadric(eye, dir, surfaces[i].surface);
        if (t_hit > 0.0f && t_hit < t)
        {
            idx = i;
            t = t_hit;
        }
    }
    return t;

}


vec3 surfaceRadiance(int idx, vec3 normal, vec3 dir)
{
    vec3 radiance = surfaces[idx].material.ambient;
    vec3 reflection = reflect(dir, normal);
    for (int i = 0; i < lights_num; i++)
    {
        if (lights[i].type == 0) // Directional
        {
            vec3 reflection = reflect(dir, normal);
            vec3 halfwayDir = normalize(lights[i].position + dir);
            vec3 surf_rad = max(0.0, dot(normal, lights[i].position)) * surfaces[idx].material.diffuse + pow(max(dot(normal, halfwayDir), 0.0), surfaces[idx].material.shininess) * surfaces[idx].material.specular;
            radiance += surf_rad * lights[i].color;
        }
    }
    return radiance;
}

#define RAY_CASTS 10

void main()
{   vec4 eye = vec4(eyePos, 1.0); 
    vec4 dir = vec4(normalize(rayDir), 0.0);
    vec3 attenuer_coeff = vec3(1.0f, 1.0f, 1.0f);
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < RAY_CASTS; i++)
    {
        int idx;
        float t = findClosestSurface(eye, dir, idx);
        if (t < 0.0f || t > 8000.0f) 
        {
            FragColor.rgb += attenuer_coeff * texture(skybox, dir.xyz).rgb;
            break;
        }
        vec4 hit = eye + t * dir;
        vec3 normal = normalize((hit * surfaces[idx].surface + surfaces[idx].surface * hit).xyz);
        if (dot(normal, dir.xyz) > 0.0f)
            normal = -normal;
        if (surfaces[idx].type == 0) //Diffuse
        {
            FragColor.rgb += attenuer_coeff * surfaceRadiance(idx, normal, -dir.xyz);
            attenuer_coeff *= surfaces[idx].material.diffuse;
            dir.xyz = reflect(dir.xyz, normal);
            eye.xyz = hit.xyz + 0.01f * dir.xyz;
        }
        else if (surfaces[idx].type == 1) // Reflective
        {
            dir.xyz = reflect(dir.xyz, normal);
            eye.xyz = hit.xyz + 0.01f * dir.xyz;

        }
        else if (surfaces[idx].type == 2) // Refractive
        {
            //TODO
        }
    }
}