//
//  Cube.cpp
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 18/06/25.
//
#include "Cube.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Geometry::Cube::Cube(const glm::vec3 center, const glm::vec3 factor){
	
	// after chaning the vertices value we now create and bind it to a buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// we now change the cube verts with scaleFactor and translate it
	modelMatrix = glm::translate(modelMatrix, center);
	modelMatrix = glm::scale(modelMatrix, factor);
}

void Geometry::Cube::draw() const{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, sizeof(cubeIndices)/sizeof(unsigned), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::Cube::translate(const glm::vec3 translateVector){
	modelMatrix = glm::translate(modelMatrix, translateVector);
}

void Geometry::Cube::rotate(const glm::vec3 rotateVector, const float radians){
	modelMatrix = glm::rotate(modelMatrix, radians, rotateVector);
}

void Geometry::Cube::scale(const glm::vec3 factor){
	modelMatrix = glm::scale(modelMatrix, factor);
}
const glm::mat4 Geometry::Cube::model() const{
	return modelMatrix;
}
