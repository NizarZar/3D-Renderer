#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	// link vbo attributes 
	vao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(float)));
	vao.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	vao.unbind();
	VBO.unbind();
	EBO.unbind();
}

void Mesh::draw( Shader& shader) {
	shader.use();
	vao.bind();

	unsigned int diffuseNum = 0;
	unsigned int specularNum = 0;
	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(diffuseNum++);
		}
		else if (type == "specular") {
			num = std::to_string(specularNum++);
		}
		textures[i].textureUnit(shader, (type + num).c_str(), i);
		textures[i].bind();
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
