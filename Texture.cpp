#include "Texture.h"

Texture::Texture(const char* image, const char* texType, GLenum slot) {
	this->type = texType;
	int imageWidth, imageHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;
	data = stbi_load(image, &imageWidth, &imageHeight, &nrChannels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	// algorithm to make image small or big
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configurate the texture pattern 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (nrChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageHeight, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageHeight, imageWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageHeight, imageWidth, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	}
	else {
		throw std::invalid_argument("Texture recognition failed!");
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);


}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::deleteTexture() {
	glDeleteTextures(1, &ID);
}
void Texture::textureUnit(Shader shader, const char* uniform, GLuint unit) {
	shader.use();
	shader.setInt(uniform, unit);
}