#include "EBO.h"
#include "Mesh.h"

EBO::EBO(std::vector<GLuint>& indices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW);
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::deleteEBO() {
	glDeleteBuffers(1, &ID);
}