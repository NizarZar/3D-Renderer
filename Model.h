#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imfilebrowser.h"


class Model {
public:
	Model(Shader shader, int i);
	float getSizeX();
	float getSizeY();
	float getSizeZ();

	void setSizeX(float value);
	void setSizeY(float value);
	void setSizeZ(float value);

	float getPositionX();
	float getPositionY();
	float getPositionZ();

	void setPositionX(float value);
	void setPositionY(float value);
	void setPositionZ(float value);



private:
	float positionX;
	float positionY;
	float positionZ;

	float sizeX;
	float sizeY;
	float sizeZ;
};


