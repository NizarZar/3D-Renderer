#version 330 core

// position layout
layout (location = 0) in vec3 aPos;
// normal layout
layout (location = 1) in vec3 aNormal;
// texture layout
layout (location = 2) in vec2 aTexCoord;
  
// output texture coordinates
out vec2 TexCoord;
// output the normal 
out vec3 Normal;
// output current position
out vec3 currentPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float sizeX;
uniform float sizeY;
uniform float sizeZ;

void main()
{
    TexCoord = aTexCoord;
    Normal = aNormal;
    currentPos = vec3(model * vec4(aPos, 1.0f));

    // output
    gl_Position = projection * view  * model * vec4(aPos.x * sizeX, aPos.y * sizeY, aPos.z * sizeZ, 1.0f);

}