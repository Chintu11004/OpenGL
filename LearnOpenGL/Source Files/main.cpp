#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// own custom header files
#include "Shader.h"
#include "ProcessTexture.h"
#include "Camera.h"
#include "Cube.h"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.13159265

GLfloat viewCoords[] = {0.0f, 0.0f, 0.0f};
void processInput(GLFWwindow* window);
void serpinskiTriangle(Shader shader, glm::mat4 trans, int depth);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Camera
Camera::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;

// Time
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

// Mouse
float lastX = WIDTH/2, lastY = HEIGHT/2;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // *required* on mac 
    #endif

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
       {
           std::cout << "Failed to initialize GLAD" << std::endl;
           return -1;
       }
	
	/*// holds the file paths
	std::array<TextureFile::TextureLocation, 2> textures = {{
		{"Texture/container.jpg", TextureFile::FileFormat::JPG, GL_CLAMP_TO_EDGE},
		{"Texture/awesomeface.png", TextureFile::FileFormat::PNG, GL_REPEAT}
	}};
	// holds the textureIDs
	std::array<GLuint, 2> texIDs = {};
	
	// initializes the textureIDs
	for (int i = 0; i < 2; i++){
		texIDs[i] = TextureFile::processTexture(textures[i].filePath, textures[i].format, textures[i].type);
	}*/
	// Shader
	Shader myShader("Shader/Basic.vsh",
					"Shader/Basic.fsh");
	Geometry::Cube myCube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	float currFrameTime = 0.0f;
	
	while (!glfwWindowShouldClose(window)) {
		currFrameTime = glfwGetTime();
		deltaTime = currFrameTime - lastFrameTime;
		lastFrameTime = currFrameTime;
		
        processInput(window);
		
        
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texIDs[0]);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texIDs[1]);
		
		myShader.use();
		// we set the textures
		//myShader.setInt("texture0", 0);
		//myShader.setInt("texture1", 1);
		// we set the transform matrix
		glm::mat4 view = camera.GetViewMatrix();
		myShader.setMat4("view", true, view);
		myShader.setMat4("projection", true, projection);
		myShader.setMat4("model", true, myCube.model());
		myCube.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos; lastY = ypos;
	
	camera.ProcessMouseMovement(xOffset, yOffset);
}
