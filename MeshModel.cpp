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
