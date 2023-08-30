#include "Model.h"


Model::Model() {
	this->name = "Object";
	this->id = 0;
	this->positionX = 0.0f;
	this->positionY = 0.0f;
	this->positionZ = 0.0f;

	this->sizeX = 1.0f;
	this->sizeY = 1.0f;
	this->sizeZ = 1.0f;
}

Model::Model(std::string name, int id) {
	this->name = name;
	this->id = id;
	this->positionX = 0.0f;
	this->positionY = 0.0f;
	this->positionZ = 0.0f;

	this->sizeX = 1.0f;
	this->sizeY = 1.0f;
	this->sizeZ = 1.0f;


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

std::string Model::getName() {
	return name;
}
void Model::setName(std::string newName) {
	name = newName;
}

int Model::getID() {
	return id;
}


