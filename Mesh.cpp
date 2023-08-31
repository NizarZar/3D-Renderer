#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	vao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(float)));
	vao.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
}
