#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// own custom header files
#include "Shader.h"
#include "ProcessTexture.h"


void processInput(GLFWwindow* window);
void serpinskiTriangle(Shader shader, glm::mat4 trans, int depth);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // *required* on mac 
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mac GL 3.3", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
       {
           std::cout << "Failed to initialize GLAD" << std::endl;
           return -1;
       }

    GLfloat verts[] = {
		// verts			//colors			//texCoords
        -1.f, -1.f, 0.0f, 	1.0f, 0.0f, 0.0f, 	0.0f, 0.0f, 	// bottom-left
        1.f, -1.f, 0.0f, 	0.0f, 1.0f, 0.0f, 	1.0f, 0.0f, 	// bottomr-right
        0.5f, 0.5f, 0.0f, 	0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, 	// top-right
		-0.5f, 0.5f, 0.0f, 	1.0f, 1.0f, 0.0f, 	0.0f, 1.0f, 	// top-left
		0.0f, 1.f, 0.0f, 	0.0f, 0.0f, 1.0f, 	1.0f, 1.0f		// top-middle
    };
	
	GLuint indices[] = {
		0, 1, 4
	};
	
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
	
	// holds the file paths
	std::array<TextureFile::TextureLocation, 2> textures = {{
		{"/Users/tejassrinivasan/Documents/Metal_Projects/OpenGLOnMac/LearnOpenGL/LearnOpenGL/Texture/container.jpg", TextureFile::FileFormat::JPG, GL_CLAMP_TO_EDGE},
		{"/Users/tejassrinivasan/Documents/Metal_Projects/OpenGLOnMac/LearnOpenGL/LearnOpenGL/Texture/awesomeface.png", TextureFile::FileFormat::PNG, GL_REPEAT}
	}};
	// holds the textureIDs
	std::array<GLuint, 2> texIDs = {};
	
	// initializes the textureIDs
	for (int i = 0; i < 2; i++){
		texIDs[i] = TextureFile::processTexture(textures[i].filePath, textures[i].format, textures[i].type);
	}
	
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// Shader
	Shader myShader("/Users/tejassrinivasan/Documents/Metal_Projects/OpenGLOnMac/LearnOpenGL/LearnOpenGL/Shader/Basic.vsh",
					"/Users/tejassrinivasan/Documents/Metal_Projects/OpenGLOnMac/LearnOpenGL/LearnOpenGL/Shader/Basic.fsh");
	//transformation matrix

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texIDs[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texIDs[1]);
		
		glBindVertexArray(VAO);
		myShader.use();
		// we set the textures
		myShader.setInt("texture0", 0);
		myShader.setInt("texture1", 1);
		// we set the transform matrix
		glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		//myShader.setMat4("transform", true, glm::mat4(1.0f));
		serpinskiTriangle(myShader, trans, 8);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void serpinskiTriangle(Shader shader, glm::mat4 trans, int depth){
	if (depth < 0)
		return;
	
	// draw the three triangles
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.0f));
	
	// left triangle
	shader.setMat4("transform", true, glm::translate(trans, glm::vec3(-1.f, -1.f, 0.0f)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	shader.setMat4("transform", true, glm::translate(trans, glm::vec3(1.f, -1.f, 0.0f)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	shader.setMat4("transform", true, glm::translate(trans, glm::vec3(0.0f, 1.f, 0.f)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	depth--;

	// left tiangle
	serpinskiTriangle(shader, glm::translate(trans, glm::vec3(-1.f, -1.f, 0.0f)), depth);
	serpinskiTriangle(shader, glm::translate(trans, glm::vec3(1.f, -1.f, 0.0f)), depth);
	serpinskiTriangle(shader, glm::translate(trans, glm::vec3(0.0f, 1.f, 0.0f)), depth);
}

