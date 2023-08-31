#pragma once
#include <glad/glad.h>
#include "VBO.h"
class VAO
{
public:
	GLuint ID;
	VAO();

	void linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void deleteVAO();
private:
	static GLuint totalNumAttrib;
};

