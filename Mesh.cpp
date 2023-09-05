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

void Mesh::draw(Shader& shader, glm::mat4 matrix = glm::mat4(1.0f), glm::vec3 translation = glm::vec3(0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
	glm::vec3 scale = glm::vec3(1.0f)) {
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
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rota = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	trans = glm::translate(trans, translation);
	rota = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rota));
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
