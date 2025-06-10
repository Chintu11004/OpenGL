#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
  

class Shader
{
public:
    // the program ID
    GLuint ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    
    // utility uniform functions
    // set a uniform boolean value
    void setBool(const std::string &name, GLboolean value) const;
    // set a uniform int value
    void setInt(const std::string &name, GLint value) const;
    // set a unform float value
    void setFloat(const std::string &name, GLfloat value) const;
    // set a uniform vec4 value
    void setVec4(const std::string &name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const;
    // set a uniform vec3 value
    void setVec3(const std::string &name, GLfloat value1, GLfloat value2, GLfloat value3) const;
	// set a uniform mat4 value
	void setMat4(const std::string &name, bool colMajorTrue, glm::mat4 trans) const;
};
  
#endif
