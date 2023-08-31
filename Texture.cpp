#include "Texture.h"

Texture::Texture(const char* image, const char* texType, GLenum slot, GLenum format, GLenum pixelType) {
	this->type = texType;
	int imageWidth, imageHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;
	data = stbi_load(image, &imageWidth, &imageHeight, &nrChannels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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