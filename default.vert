#version 330 core

// position layout
layout (location = 0) in vec3 aPos;
// normal layout
layout (location = 1) in vec3 aNormal;
// texture layout
layout (location = 2) in vec2 aTexCoord;
  
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float sizeX;
uniform float sizeY;
uniform float sizeZ;

void main()
{
    gl_Position = projection * view  * model * vec4(aPos.x * sizeX, aPos.y * sizeY, aPos.z * sizeZ, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}