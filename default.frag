#version 330 core

out vec4 FragColor;
in vec2 TexCoord;


uniform sampler2D texture1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

in vec3 Normal;
in vec3 currentPos;


void main()
{
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - currentPos);

    float diffuse = max(dot(normal, lightDirection), 0.0f);
    float specular = 0.5f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float spec = specularAmount * specular;


    FragColor = texture(texture1, TexCoord) * lightColor *  (diffuse + ambient + specular);

} 