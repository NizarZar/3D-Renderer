#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	this->type = texType;
	int imageWidth, imageHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;
	data = stbi_load(image, &imageWidth, &imageHeight, &nrChannels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texType);
	stbi_image_free(data);


}

void Texture::bind() {
	glBindTexture(this->type, ID);
}
void Texture::unbind() {
	glBindTexture(this->type, 0);
}
void Texture::deleteTexture() {
	glDeleteTextures(1, &ID);
}
void Texture::textureUnit(Shader shader, const char* uniform, GLuint unit) {
	shader.use();
	shader.setInt(uniform, unit);
}