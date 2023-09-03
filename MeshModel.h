#pragma once
#include "include/json.h"
#include "Mesh.h"

using json = nlohmann::json;

class MeshModel
{
public:
	MeshModel(const char* file);
	void draw(Shader& shader);
private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// methods
	std::vector<unsigned char> getData();

};

