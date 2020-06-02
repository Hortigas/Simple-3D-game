#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <SOIL2.h>
#include <math.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "MVP.h"
#include "Camera.h"
#include "TPCamera.h"
#include "Mesh.h"
#include "Model.h"
#include "Veiculo.h"
#include "SkyBox.h"
#include "Terrain.h"

// Matrizes
MVP mvp, Skymvp, cam;

// Helicoptero
Veiculo heli;

// Camera
TPCamera TPcamera;
Camera camera;
bool ThirdPerson = true;
bool iluminacao = true;
bool click, click2;

// Mouse
float lastX = WINDOW_WIDTH / 2.f, lastY = WINDOW_HEIGHT / 2.f;
bool firstMouse=true;

// FPS
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float anguloDaElice;
float x = 0;
float speed;

// Functions
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

int main() {
	GLFWwindow* window;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TP2", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	std::cout << glGetString(GL_VERSION) << std::endl;

	//configs
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Shaders
	Shader shader("VertexShader.hlsl", "FragmentShader.hlsl");
	Shader lightShader("LightVertexShader.hlsl", "LightFragmentShader.hlsl");
	Shader skyBoxShader("SkyBoxVertexShader.hlsl", "SkyBoxFragmentShader.hlsl");

	float vertices[] = { // Cube
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	//Criando Vertex Array e Vertex Buffer do Cubo 
	VertexArray cubeVA;
	VertexBuffer cubeVB(vertices, sizeof(vertices));
	//Buffer de vertices do Cubo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(0);
	//Buffer de normais do Cubo
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Buffer de texturas do Cubo
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//Criando Vertex Array da Luz
	VertexArray LightVA;
	//Buffer de vertices de um Cubo
	cubeVB.Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	// Models
	Model tree("res/objects/tree/lowpolytree.obj");
	Model tree2("res/objects/tree2/tree.obj");
	Model havoc("res/objects/havoc/havoc.obj");

	Model models[] = { tree, tree2 };

	// Skybox
	SkyBox skybox;

	// Terrain
	Terrain terrain;
	unsigned int grass = loadTexture("res/textures/grass.jpg");

	while (glfwWindowShouldClose(window) != GLFW_TRUE) {

		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//FPS
		float currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Controls
		glfwSetCursorPosCallback(window, mouse_callback);
		processInput(window);

		shader.Bind();
		shader.setBool("iluminacao", iluminacao);
		shader.setVec3("pointLights[0].position",0.f,1.f,0.f);
		shader.setVec3("pointLights[1].position", heli.Position);
		shader.setVec3("spotLight.position", heli.Position);
		shader.defLights();

		if (ThirdPerson) {
			mvp.ViewMatrix = TPcamera.GetViewMatrix(heli);
			Skymvp.ViewMatrix = glm::mat4(glm::mat3(TPcamera.GetViewMatrix(heli)));
			shader.setVec3("viewPos", TPcamera.Position);
		}
		else {
			mvp.ViewMatrix = camera.GetViewMatrix();
			Skymvp.ViewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
			shader.setVec3("viewPos", camera.Position);
		}

		// Drawing Helicopter
		heli.calculations(mvp, deltaTime);
		havoc.DrawVeiculo(shader, mvp, deltaTime);

		// Drawing Lights
		lightShader.Bind();
		lightShader.setVec3("lightColor", 1.f, 1.f, 1.f);
		for (unsigned int i = 0; i < 1; i++)
		{
			mvp.resetModel();
			mvp.translate(glm::vec3(0.f,1.f,0.f));
			mvp.scale(0.3f);
			LightVA.Bind();
			mvp.use(lightShader);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Drawing Skybox
		skyBoxShader.Bind();
		LightVA.Bind();
		Skymvp.use(skyBoxShader);
		skybox.draw();

		// Drawing Terrain
		mvp.resetModel();
		terrain.draw(shader, heli, mvp, models, grass);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(lightShader.GetID());
	glDeleteProgram(skyBoxShader.GetID());
	glDeleteProgram(shader.GetID());
	glfwDestroyWindow(window);
	glfwTerminate();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	if (ThirdPerson) {
		TPcamera.ProcessMouseMovement(yoffset);
		heli.ProcessMouseMovement(xoffset, yoffset);
	}
	else
		camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow* window)
{
	bool parado = true;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		heli.ProcessKeyBoard(FORWARDV, deltaTime, mvp);
		parado = false;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		heli.ProcessKeyBoard(BACKWARDV, deltaTime, mvp);
		parado = false;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		heli.ProcessKeyBoard(LEFTV, deltaTime, mvp);
		parado = false;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		heli.ProcessKeyBoard(RIGHTV, deltaTime, mvp);
		parado = false;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		heli.ProcessKeyBoard(UP, deltaTime, mvp);
		parado = false;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		heli.ProcessKeyBoard(DOWN, deltaTime, mvp);
		parado = false;
	}
	if (parado) {
		heli.ProcessKeyBoard(STATIC, deltaTime, mvp);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && click == true) {
		if (ThirdPerson) {
			camera.Position = heli.Position;
			ThirdPerson = false;
		}
		else
			ThirdPerson = true;
		click = false;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
		click = true;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && click2 == true) {
		if (iluminacao)
			iluminacao = false;
		else
			iluminacao = true;
		click2 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
		click2 = true;
	}
}

unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	int width, height;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	if (0 == data)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D); 
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}