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

	// variables
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<std::string> loadedTextureNames;
	std::vector<Texture> loadedTextures;
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationMeshes;
	std::vector<glm::quat> rotationMeshes;
	std::vector<glm::vec3> scaleMeshes;
	std::vector<glm::mat4> matrices;


	// methods
	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords);


	void loadMeshes(unsigned int meshIndex);
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));


	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

	void draw(Shader& shader);

};

