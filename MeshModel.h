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
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

};

