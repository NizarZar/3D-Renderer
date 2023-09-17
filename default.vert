#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormalCoord;
  
out vec2 TexCoord;
out vec3 Normal;
out vec3 currentPos;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float sizeX;
uniform float sizeY;
uniform float sizeZ;


void main()
{
    gl_Position = projection * view  * model * vec4(aPos.x * sizeX, aPos.y * sizeY, aPos.z * sizeZ, 1.0f);
    TexCoord = aTexCoord;
    currentPos = vec3(model * vec4(aPos.x * sizeX, aPos.y * sizeY, aPos.z * sizeZ, 1.0f));
    Normal = aNormalCoord;
    color = aColor;
}