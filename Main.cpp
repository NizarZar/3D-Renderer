#include "Model.h"


#define RECTANGLE_ID 0
#define TRIANGLE_ID 1
#define LIGHTCUBE_ID 2

// variables

// screen 
const float SCREEN_WIDTH = 1280.f;
const float SCREEN_HEIGHT = 720.0f;

// texture files
std::string textureFilePathString;
const char* textureFilePath;


// shapes vertices and indices
// other rectangle
 /*
 * // rectangle
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
 */

GLfloat rectangleVertices[] = {
	// coordinates			// colors				 // text coord   // normal
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};
GLuint rectangleIndices[] = {
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


GLfloat lightVertices[] =
{	// coordinates
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


// grid view
bool isGridView = false;

// object size

float sizeX = 1.0f;
float sizeY = 1.0f;
float sizeZ = 1.0f;

// camera right click look state
bool lookState = false;

// stored shapes you can create
std::vector<std::string> shapes;
std::vector<Model> sceneObjects;
Model currentObject;

// input value
unsigned int input;

// object on scene ID calculator
int objectID = 0;
std::string name = "";

// VBO, VAO
GLuint VBO, VAO, EBO;
// light cube VBO, VAO and EBO
GLuint lightVBO, lightVAO, lightEBO;


// object position
float positionY = 0.0f;
float positionX = 0.0f;
float positionZ = 0.0f;

// file dialog
ImGui::FileBrowser fileBrowser;

// camera
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


// settings camera
bool fMouse = true;
float yaw = -90.f;
float pitch = 0.0f;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float fov = 45.f;

// turn on/off camera look around
bool lookAround = false;

// time and frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f) {
		fov = 1.0f;
	}
	if (fov > 90.f) {
		fov = 90.f;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		lookAround = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		lookAround = false;
	}

}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (fMouse) {
		lastX = xpos;
		lastY = ypos;
		fMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	if (lookAround) {
		yaw += xoffset;
		pitch += yoffset;
	}
	// if out of bound 
	if (pitch > 89.f) {
		pitch = 89.f;
	}
	if (pitch < -89.f) {
		pitch = -89.f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPosition += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPosition -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		lookAround = true;
		std::cout << "Left pressed" << std::endl;
	}
	

}

void setDefaultSettings() {
		sizeX = 1.0f;
		sizeY = 1.0f;
		sizeZ = 1.0f;
		positionX = 0.0f;
		positionY = 0.0f;
		positionZ = 0.0f;
}

void drawRectangle() {
	


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// ST
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void drawLightCube() {
	
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	std::cout << "created" << std::endl;
}

void drawGrid() {

}

void shapesGUI() {
	ImGui::Begin("Spawnable Objects");
	ImGui::InputText("Name", &name, sizeof(name));
	if (ImGui::Button("Rectangle")) {
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i].getName() == name) {
				name += std::to_string(objectID);
			}
		}
		if (name == "") {
			name = "rectangle";
		}
		Model model(name, objectID, RECTANGLE_ID);
		sceneObjects.push_back(model);
		objectID++;
	}
	if (ImGui::Button("Light (Cube)")) {
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i].getName() == name) {
				name += std::to_string(objectID);
			}
		}
		if (name == "") {
			name = "LightCube";
		}
		Model model(name, objectID, LIGHTCUBE_ID);
		sceneObjects.push_back(model);
		objectID++;
	}
	if (ImGui::Button("Clear")) {
		while (!sceneObjects.empty()) {
			sceneObjects.pop_back();
		}
		objectID = 0;
	}
	ImGui::End();
}

void settingsGUI() {

	fileBrowser.SetTitle("Select texture");

	ImGui::Begin("Settings");
	ImGui::Checkbox("Grid View (not implemented)", &isGridView);
	ImGui::Text("Position:");
	// slider to change the position of the current object as well as store new information on the list of sceneObjects
	if (ImGui::SliderFloat("X Axis", &currentObject.positionX, -5.0f, 5.0f)) {
		//std::cout << currentObject.positionX << std::endl;
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].positionX = currentObject.positionX;
			}
		}
	}
	if (ImGui::SliderFloat("Y Axis", &currentObject.positionY, -5.0f, 5.0f)) {
		//std::cout << currentObject.positionX << std::endl;
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].positionY = currentObject.positionY;
			}
		}
	}
	if (ImGui::SliderFloat("Z Axis", &currentObject.positionZ, -5.0f, 5.0f)) {
		//std::cout << currentObject.positionX << std::endl;
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].positionZ = currentObject.positionZ;
			}
		}
	}
	ImGui::Text("Scale: ");
	if (ImGui::SliderFloat("X", &currentObject.sizeX, 0.f, 5.0f)) {
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].sizeX = currentObject.sizeX;
			}
		}
	}
	if (ImGui::SliderFloat("Y", &currentObject.sizeY, 0.f, 5.0f)) {
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].sizeY = currentObject.sizeY;
			}
		}
	}
	if (ImGui::SliderFloat("Z", &currentObject.sizeZ, 0.f, 5.0f)) {
		for (int i = 0; i < sceneObjects.size(); i++) {
			if (currentObject.getID() == sceneObjects[i].getID()) {
				sceneObjects[i].sizeZ = currentObject.sizeZ;
			}
		}
	}
	ImGui::Text("Camera: ");
	ImGui::SliderFloat("FOV", &fov, 1.f, 90.f);
	ImGui::Text("Texture: ");
	if (ImGui::Button("Select Texture")) {
		fileBrowser.Open();
	}
	ImGui::End();
	fileBrowser.Display();
	if (fileBrowser.HasSelected()) {
		textureFilePathString = fileBrowser.GetSelected().string();
		textureFilePath = textureFilePathString.c_str();
		fileBrowser.ClearSelected();
	}
}

void sceneGUI() {
	ImGui::Begin("Scene");
	for (int i = 0; i < sceneObjects.size(); i++) {
		bool selectable = ImGui::Selectable(sceneObjects[i].getName().c_str(), false);
		if (selectable) {
			if (currentObject.getID() != sceneObjects[i].getID()) {
				currentObject = sceneObjects[i];
			}
			std::cout << "Current Selection: " << currentObject.getName() <<std::endl;
		}

	}
	ImGui::End();
}

int main() {
	// set up glfw and version opengl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	GLFWwindow* window = glfwCreateWindow((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, "3D Renderer", NULL, NULL);
	if (window == nullptr) {
		std::cout << "FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// load glad before opengl
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return -1;
	}
	
	// shader initialization
	Shader shader("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	// opengl viewport
	glViewport(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	drawLightCube();
	drawRectangle();
	


	glEnable(GL_DEPTH_TEST);

	// texture generation
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// initialize light color as white by default
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	int width, height, nrChannels;
	unsigned char* data;
	
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); 
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// frame check
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// check input
		processInput(window);
		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		settingsGUI();
		shapesGUI();
		sceneGUI();

		if (sceneObjects.empty()) {
			setDefaultSettings();
		}

		// texture loader
		stbi_set_flip_vertically_on_load(true);
		if (textureFilePath == nullptr) {
			textureFilePathString = "";
			textureFilePath = textureFilePathString.c_str();
		}
		data = stbi_load("assets/dirt_block.png", &width, &height, &nrChannels, 0);
		//data = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.f);
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		shader.setInt("texture1", 0);
		shader.use();
		// camera view
		int viewLoc = glGetUniformLocation(shader.getID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// camera projection
		int projectionLoc = glGetUniformLocation(shader.getID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// light color
		glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		lightShader.use();
		int projectionLightLoc = glGetUniformLocation(lightShader.getID(), "projection");
		glUniformMatrix4fv(projectionLightLoc, 1, GL_FALSE, glm::value_ptr(projection));
		int viewLightLoc = glGetUniformLocation(lightShader.getID(), "view");
		glUniformMatrix4fv(viewLightLoc, 1, GL_FALSE, &view[0][0]);
		glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		// drawing all the shapes in the list
		for (int i = 0; i < sceneObjects.size(); i++) {
			float currentPositionX;
			if (sceneObjects[i].getTypeID() == RECTANGLE_ID) {
				shader.use();
				glBindVertexArray(VAO);
				glm::mat4 model = glm::mat4(1.0f);
				if (sceneObjects[i].getID() == currentObject.getID()) {
					currentPositionX = currentObject.getPositionX() + i * 0.5f;
					model = glm::translate(model, glm::vec3(currentPositionX, currentObject.getPositionY(), currentObject.getPositionZ()));
					shader.setFloat("sizeX", currentObject.getSizeX());
					shader.setFloat("sizeY", currentObject.getSizeY());
					shader.setFloat("sizeZ", currentObject.getSizeZ());
				}
				else {
					currentPositionX = sceneObjects[i].getPositionX() + i * 0.5f;
					model = glm::translate(model, glm::vec3(currentPositionX, sceneObjects[i].getPositionY(), sceneObjects[i].getPositionZ()));
					shader.setFloat("sizeX", sceneObjects[i].getSizeX());
					shader.setFloat("sizeY", sceneObjects[i].getSizeY());
					shader.setFloat("sizeZ", sceneObjects[i].getSizeZ());
				}
				model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
				model = glm::rotate(model, -glm::radians(0.f), glm::vec3(1.0f, 1.0f, 1.0f));
				int modelLoc = glGetUniformLocation(shader.getID(), "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawElements(GL_TRIANGLES, sizeof(rectangleIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
			}
			else if (sceneObjects[i].getTypeID() == LIGHTCUBE_ID) {
				lightShader.use();
				glBindVertexArray(lightVAO);
				glm::mat4 lightModel = glm::mat4(1.0f);
				if (sceneObjects[i].getID() == currentObject.getID()) {
					currentPositionX = currentObject.getPositionX() + i * 0.5f;
					lightModel = glm::translate(lightModel, glm::vec3(currentPositionX, currentObject.getPositionY(), currentObject.getPositionZ()));
				}
				else {
					currentPositionX = sceneObjects[i].getPositionX() + i * 0.5f;
					lightModel = glm::translate(lightModel, glm::vec3(currentPositionX, sceneObjects[i].getPositionY(), sceneObjects[i].getPositionZ()));
				}
				lightModel = glm::rotate(lightModel, -glm::radians(0.f), glm::vec3(1.0f, 1.0f, 1.0f));
				glUniformMatrix4fv(glGetUniformLocation(lightShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
				glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

			}
		}
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// check buffers and events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	glDeleteBuffers(1, &lightEBO);
	shader.remove();
	lightShader.remove();

	glfwTerminate();
	return 0;
}
