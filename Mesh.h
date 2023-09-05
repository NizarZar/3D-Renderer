#pragma once
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh(std::vector <Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO vao;

	void draw(Shader& shader, glm::mat4 matrix = glm::mat4(1.0f), glm::vec3 translation = glm::vec3(0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f));

	
};

