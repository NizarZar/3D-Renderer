#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imfilebrowser.h"


class Model {
public:
	Model(std::string name, int id);
	Model();
	float getSizeX();
	float getSizeY();
	float getSizeZ();


	float getPositionX();
	float getPositionY();
	float getPositionZ();

	std::string getName();
	void setName(std::string newName);
	int getID();
	float positionX;
	float positionY;
	float positionZ;

	float sizeX;
	float sizeY;
	float sizeZ;


private:
	std::string name;
	int id;
};


