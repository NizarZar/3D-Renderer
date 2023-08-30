#include "Model.h"


// variables


// screen 
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;

std::string textureFilePathString;
const char* textureFilePath;

// object size

float sizeX = 1.0f;
float sizeY = 1.0f;
float sizeZ = 1.0f;

bool lookState = false;

// stored shapes you can create
std::vector<std::string> shapes;


unsigned int input;

int shapesI = 0;

// VBO, VAO
GLuint VBO, VAO;

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

bool fMouse = true;
float yaw = -90.f;
float pitch = 0.0f;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float fov = 45.f;

bool lookAround = false;

// time
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

void drawTriangle() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



}

void drawRectangle() {
	// rectangle
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



	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


}

void settingsGUI() {

	fileBrowser.SetTitle("Select texture");

	ImGui::Begin("Settings");
	ImGui::Text("Position:");
	ImGui::SliderFloat("X Axis", &positionX, -3.0f, 3.0f);
	ImGui::SliderFloat("Y Axis", &positionY, -3.0f, 3.0f);
	ImGui::SliderFloat("Z Axis", &positionZ, -3.0f, 3.0f);
	ImGui::Text("Scale: ");
	ImGui::SliderFloat("X", &sizeX, 0.f, 3.0f);
	ImGui::SliderFloat("Y", &sizeY, 0.f, 3.0f);
	ImGui::SliderFloat("Z", &sizeZ, 0.f, 3.0f);
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

void shapesGUI() {
	ImGui::Begin("Shapes");
	if (ImGui::Button("Rectangle")) {
		std::string rectangle = "rectangle";
		shapes.push_back(rectangle);
		shapesI++;
	}
	//if (ImGui::Button("Triangle")) {
		//std::cout << "Triangle!" << std::endl;
		//shapes.push_back("triangle");
		//shapesI++;
	//}
	//if (ImGui::Button("Delete Previous")) {
		//if (!shapes.empty()) {
		//	shapes.pop_back();
		//	shapesI--;
		//}
	//}
	if (ImGui::Button("Clear")) {
		while (!shapes.empty()) {
			shapes.pop_back();
			shapesI = 0;
		}
	}
	ImGui::End();
}

void sceneGUI() {
	ImGui::Begin("Scene");
	for (int i = 0; i < shapes.size(); i++) {
		ImGui::Text(shapes[i].c_str());
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

	// opengl viewport
	glViewport(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	drawRectangle();
	

	glEnable(GL_DEPTH_TEST);



	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ST
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture generation
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

		if (shapes.empty()) {
			setDefaultSettings();
		}

		stbi_set_flip_vertically_on_load(true);
		if (textureFilePath == nullptr) {
			textureFilePathString = "";
			textureFilePath = textureFilePathString.c_str();
		}
		data = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);


		shader.use();
		shader.setInt("texture1", 0);
		// camera view
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		int viewLoc = glGetUniformLocation(shader.getID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// camera projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.f);

		int projectionLoc = glGetUniformLocation(shader.getID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAO);

		for (int i = 0; i < shapes.size(); i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
			model = glm::rotate(model, -glm::radians(45.f)*i, glm::vec3(1.0f, 1.0f, 1.0f));
			int modelLoc = glGetUniformLocation(shader.getID(), "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		shader.setFloat("sizeX", sizeX);
		shader.setFloat("sizeY", sizeY);
		shader.setFloat("sizeZ", sizeZ);

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
	shader.remove();

	glfwTerminate();
	return 0;
}
