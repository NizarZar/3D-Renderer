#version 330 core
out vec4 FragColor;

// input text coordinate
in vec2 TexCoord;
// input normal
in vec3 Normal;
// input current position
in vec3 currentPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
    FragColor = texture(texture1, TexCoord);

} 