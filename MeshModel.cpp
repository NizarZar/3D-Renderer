#include "MeshModel.h"

MeshModel::MeshModel(const char* file) {
	std::string text = get_file_contents(file);
	JSON = json::parse(text);
	this->file = file;
	data = getData();

	traverseNode(0);
}

std::vector<unsigned char> MeshModel::getData() {
	std::string bytesText;
	std::string uriKey = JSON["buffers"][0]["uri"];

	std::string fileString = std::string(file);
	std::string fileDir = fileString.substr(0, fileString.find_last_of('/')+1);
	bytesText = get_file_contents((fileDir + uriKey).c_str());

	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

std::vector<float> MeshModel::getFloats(json accessor) {
	std::vector<float> floatVec;

	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVertice;
	if (type == "SCALAR") {
		numPerVertice = 1;
	}
	else if (type == "VEC2") {
		numPerVertice = 2;
	}
	else if (type == "VEC3") {
		numPerVertice = 3;
	}
	else if (type == "VEC4") {
		numPerVertice = 4;
	}
	else {
		throw std::invalid_argument("Invalid Type");
	}

	unsigned int dataStart = byteOffset + accByteOffset;
	unsigned int dataLength = count * 4 * numPerVertice;
	for (unsigned int i = dataStart; i < (dataStart + dataLength); i) {
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floatVec.push_back(value);
	}

	return floatVec;

}

std::vector<GLuint> MeshModel::getIndices(json accessor) {
	std::vector<GLuint> indices;

	unsigned int buffViewIndice = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteoffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewIndice];
	unsigned int byteOffset = bufferView["byteOffset"];
	unsigned int dataStart = byteOffset + accByteOffset;

	if (componentType == 5125) {
		for (unsigned int i = dataStart; i < byteOffset + accByteOffset + count*4; i) {
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);

		}
	}
	else if (componentType == 5123) {
		for (unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5122) {
		for (unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof( short));
			indices.push_back((GLuint)value);
		}
	}
	return indices;
}

std::vector<Texture> MeshModel::getTextures()
{
	std::vector<Texture> textures;

	std::string fileString = std::string(file);
	std::string fileDir = fileString.substr(0, fileString.find_last_of('/') + 1);

	for (unsigned int i = 0; i < JSON["images"].size(); i++) {
		std::string texturePath = JSON["images"][i]["uri"];
		bool skip = false;

		for (unsigned int j = 0; j < loadedTextureNames.size(); j++) {
			if (loadedTextureNames[j] == texturePath) {
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			if (texturePath.find("baseColor") != std::string::npos) {
				Texture diffuse = Texture((fileDir + texturePath).c_str(), "diffuse", loadedTextures.size());
				textures.push_back(diffuse);
				loadedTextures.push_back(diffuse);
				loadedTextureNames.push_back(texturePath);
			}
			else if (texturePath.find("metallicRoughness") != std::string::npos) {
				Texture specular = Texture((fileDir + texturePath).c_str(), "specular", loadedTextures.size());
				textures.push_back(specular);
				loadedTextures.push_back(specular);
				loadedTextureNames.push_back(texturePath);
			}
		}
	}
	return textures;
}

std::vector<Vertex> MeshModel::assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords)
{
	std::vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++) {
		vertices.push_back(Vertex{ positions[i], normals[i], textureCoords[i] });

	}
	return vertices;
}

void MeshModel::loadMeshes(unsigned int meshIndex)
{
	unsigned int positionAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int textureAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indexAccIndex = JSON["meshes"][meshIndex]["primitives"][0]["attributes"]["indices"];

	std::vector<float> positionVec = getFloats(JSON["accessors"][positionAccIndex]);
	std::vector<glm::vec3> positions = groupFloatsVec3(positionVec);
	std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccIndex]);
	std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
	std::vector<float> textureVec = getFloats(JSON["accessors"][textureAccIndex]);
	std::vector<glm::vec2> textureUVs = groupFloatsVec2(textureVec);

	std::vector<Vertex> vertices = assembleVertices(positions, normals, textureUVs);
	std::vector<GLuint> indices = getIndices(JSON["accessors"][indexAccIndex]);
	std::vector<Texture> textures = getTextures();

	Mesh loadedMesh(vertices, indices, textures);

	meshes.push_back(loadedMesh);

}

void MeshModel::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{
	json node = JSON["nodes"][nextNode];
	
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end()) {
		float translationValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++) {
			translationValues[i] = (node["translation"][i]);
		}
		translation = glm::make_vec3(translationValues);
	}
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end()) {
		float rotationValues[4] = { node["rotation"][3], node["rotation"][0], node["rotation"][1], node["rotation"][2] };
		rotation = glm::make_quat(rotationValues);
	}
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end()) {
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++) {
			scaleValues[i] = (node["scale"][i]);
		}
		scale = glm::make_vec3(scaleValues);
	}
	glm::mat4 matrNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end()) {
		float matrValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++) {
			matrValues[i] = (node["matrix"][i]);
		}
		matrNode = glm::make_mat4(matrValues);
	}

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rota = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);
	

	trans = glm::translate(trans, translation);
	rota = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glm::mat4 matrNextNode = matrix * matrNode * trans * rota * sca;
	if (node.find("mesh") != node.end()) {
		translationMeshes.push_back(translation);
		rotationMeshes.push_back(rotation);
		scaleMeshes.push_back(scale);
		matrices.push_back(matrNextNode);
		loadMeshes(node["mesh"]);
	}

	// repeat with recursion
	if (node.find("children") != node.end()) {
		for (unsigned int i = 0; i < node["children"].size(); i++) {
			traverseNode(node["children"][i], matrNextNode);
		}
	}


}

std::vector<glm::vec2> MeshModel::groupFloatsVec2(std::vector<float> floatVec) {
	std::vector<glm::vec2> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec3> MeshModel::groupFloatsVec3(std::vector<float> floatVec)
{
	std::vector<glm::vec3> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec4> MeshModel::groupFloatsVec4(std::vector<float> floatVec)
{
	std::vector<glm::vec4> vectors;
	for (int i = 0; i < floatVec.size(); i) {
		vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

void MeshModel::draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(shader, matrices[i]);
	}
}
