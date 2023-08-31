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

	void draw(Shader& shader);

	
};

