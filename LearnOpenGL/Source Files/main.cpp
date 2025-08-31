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
#define PI 3.14159265

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
	
	// holds the file paths
	std::array<TextureFile::TextureLocation, 3> textures = {{
		{"Texture/container2.png", TextureFile::FileFormat::PNG, GL_CLAMP_TO_EDGE},
		{"Texture/container2_specular.png", TextureFile::FileFormat::PNG, GL_CLAMP_TO_EDGE},
		{"Texture/matrix.jpg", TextureFile::FileFormat::JPG, GL_CLAMP_TO_EDGE}
	}};
	// holds the textureIDs
	std::array<GLuint, 3> texIDs = {};
	
	// initializes the textureIDs
	for (int i = 0; i < 3; i++){
		texIDs[i] = TextureFile::processTexture(textures[i].filePath, textures[i].format, textures[i].type);
	}
	
	// Initialize shared cube mesh (call once at startup)
	// Shader
	Shader myShader("Shader/Basic.vsh",
					"Shader/Basic.fsh");
	Geometry::Cube containerCube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));

	Shader lightShader("Shader/Light.vsh",
					   "Shader/Light.fsh");
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	Geometry::Cube lightCube(glm::vec3(lightPos), glm::vec3(0.2f));
	
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), ((float)WIDTH/HEIGHT), 0.1f, 100.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	float currFrameTime = 0.0f;
	glm::vec3 lightColor(1.0f);//std::sin((float)glfwGetTime()));
	//float radius = 2.0f;
	
	while (!glfwWindowShouldClose(window)) {
		currFrameTime = glfwGetTime();
		deltaTime = currFrameTime - lastFrameTime;
		lastFrameTime = currFrameTime;
		
        processInput(window);
		
		// we move the light around
		//lightCube.setOrigin((glm::vec3(radius * sin(currFrameTime), radius * cos(currFrameTime), sin(currFrameTime))));
		//lightCube.scale(glm::vec3(0.2f));
        
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texIDs[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texIDs[1]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texIDs[2]);
		glm::mat4 view = camera.GetViewMatrix();

		myShader.use();
		// we set the textures
		//myShader.setInt("texture1", 1);
		// we set the transform matrix
		myShader.setMat4("view", true, view);
		myShader.setMat4("projection", true, projection);
				
		// setting up the light
		myShader.setVec3("lightColor", lightColor);
		//myShader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		//myShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		myShader.setInt("material.diffuseTexture", 0);
		myShader.setInt("material.specularTexture", 1);
		myShader.setFloat("material.shininess", 32.0f);
		myShader.setInt("material.emissiveMap", 2);
		
		myShader.setVec3("light.direction", glm::vec3(view * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)));
		myShader.setVec3("light.ambientStrength", glm::vec3(0.05f));
		myShader.setVec3("light.diffuseStrength", glm::vec3(0.5f));
		myShader.setVec3("light.specularStrength", glm::vec3(1.0f));

		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setMat4("model", true, model);
			
			containerCube.draw();
		}
		//containerCube.draw();  // Use lit VAO (position + normal)

		lightShader.use();
		lightShader.setMat4("view", true, view);
		lightShader.setMat4("projection", true, projection);
		lightShader.setMat4("model", true, lightCube.model());
		lightShader.setVec3("lightColor", lightColor);
		lightCube.draw();  // Use unlit VAO (position only)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up shared resources
    glfwTerminate();
}

void processInput(GLFWwindow* window){
	
	uint32_t mask = 0;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE) mask |= Camera::BACKWARD;
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE) mask |= Camera::FORWARD;
	if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) mask |= Camera::LEFT;
	if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) mask |= Camera::RIGHT;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) mask |= Camera::UP;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) != GLFW_RELEASE) mask |= Camera::DOWN;

	
	camera.ProcessKeyboard(mask, deltaTime);
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
