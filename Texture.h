#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	Texture(const char* image, const char* texType, GLenum slot);
	void textureUnit(Shader shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void deleteTexture();
};

