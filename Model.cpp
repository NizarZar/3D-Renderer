#include "Model.h"


Model::Model(Shader shader, int i) {
	this->positionX = 0.0f;
	this->positionY = 0.0f;
	this->positionZ = 0.0f;

	this->sizeX = 1.0f;
	this->sizeY = 1.0f;
	this->sizeZ = 1.0f;


}

void Model::setSizeX(float value) {
	this->sizeX = value;
}
void Model::setSizeY(float value) {
	this->sizeY = value;
}
void Model::setSizeZ(float value) {
	this->sizeZ = value;
}
void Model::setPositionX(float value) {
	this->positionX = value;
}
void Model::setPositionY(float value) {
	this->positionY = value;
}
void Model::setPositionZ(float value) {
	this->positionZ = value;
}

float Model::getSizeX() {
	return sizeX;
}
float Model::getSizeY() {
	return sizeY;
}
float Model::getSizeZ() {
	return sizeZ;
}
float Model::getPositionX() {
	return positionX;
}
float Model::getPositionY() {
	return positionY;
}
float Model::getPositionZ() {
	return positionZ;
}


