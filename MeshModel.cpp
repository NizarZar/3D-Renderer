#include "MeshModel.h"

MeshModel::MeshModel(const char* file) {
	std::string text = get_file_contents(file);
	JSON = json::parse(text);
	this->file = file;
	data = getData();
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
	else if (componentType = 5123) {
		for (unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType = 5122) {
		for (unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof( short));
			indices.push_back((GLuint)value);
		}
	}
	return indices;
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
