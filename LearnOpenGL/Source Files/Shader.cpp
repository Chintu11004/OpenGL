#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vShaderCode, fShaderCode;
    std::ifstream vShaderFile, fShaderFile;
    
    //ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // we now try to read the data of the shader files at a given file path
    try {
        vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
		
        vShaderFile.close(); fShaderFile.close();
        
        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR IN READING SHADER FILES" << std::endl;
    }
    const char* vShader, *fShader;
    vShader = vShaderCode.c_str();
    fShader = fShaderCode.c_str();
    
    GLuint vertex, fragment;
    int success;
    char infoLog[512];
    
    // create the shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    // now we link and compile the shaders and see if they have succesfully compiled
    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);
	
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "UNABLE TO PROPERLY COMPILE THE VERTEX SHADER AT" << vertexPath << "\nInfo Log states" << infoLog << std::endl;
    }
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShader, NULL);
	glCompileShader(fragment);
	
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "UNABLE TO PROPERLY COMPILE THE FRAGMENT SHADER AT" << fragmentPath << "\nInfo Log states" << infoLog << std::endl;
    }
    
    ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
    glLinkProgram(ID);
	
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
	glDeleteShader(vertex); glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, GLboolean value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, GLint value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, GLfloat value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec4(const std::string &name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setVec3(const std::string &name, GLfloat value1, GLfloat value2, GLfloat value3) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setVec3(const std::string &name, glm::vec3 colorVector) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), colorVector.x, colorVector.y, colorVector.z);
}

void Shader::setMat4(const std::string &name, bool colMajorTrue, glm::mat4 trans) const {
	if (colMajorTrue)
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
	else
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, glm::value_ptr(trans));
}
