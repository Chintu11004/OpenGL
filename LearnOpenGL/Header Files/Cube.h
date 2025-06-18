//
//  Cube.h
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 18/06/25.
//
#pragma once
#include <glm/glm.hpp>

namespace Geometry {
static const float cube[] = {
	// front side
	   -0.5f, -0.5f, 0.5f, //front bottom-left
	   0.5f, -0.5f, 0.5f,		//front bottom-right
	   -0.5f, 0.5f, 0.5f, //front top-left
	   0.5f, 0.5f, 0.5f, 	//front top-right
	   
	   // right side
	   0.5f, -0.5f, 0.5f, 	// right bottom-left
	   0.5f, -0.5f, -0.5f,	// right bottom-right
	   0.5f, 0.5f, 0.5f, 		//right top-left
	   0.5f, 0.5f, -0.5f, 	//right top-right
	   
	   //back side
	   0.5f, -0.5f, -0.5f, //back bottom-left
	   -0.5f, -0.5f, -0.5f,	//back bottom-right
	   0.5f, 0.5f, -0.5f, 		//back top-left
	   -0.5f, 0.5f, -0.5f, 	//back top-right
	   
	   // left side
	   -0.5f, -0.5f, -0.5f, //left bottom-left
	   -0.5f, -0.5f, 0.5f,		//left bottom-right
	   -0.5f, 0.5f, -0.5f, //left top-left
	   -0.5f, 0.5f, 0.5f, 	//left top-right
	   
	   // top side
	   0.5f, 0.5f, -0.5f, 	//top  bottom-left
	   -0.5f, 0.5f, -0.5f,		//top bottom-right
	   0.5f, 0.5f, 0.5f, 	//top top-left
	   -0.5f, 0.5f, 0.5f, 	//top top-right
	   
	   // bottom side
	   0.5f, -0.5f, -0.5f, 	//top  bottom-left
	   -0.5f, -0.5f, -0.5f,	//top bottom-right
	   0.5f, -0.5f, 0.5f, 	//top top-left
	   -0.5f, -0.5f, 0.5f, //top top-right
   };
static const unsigned cubeIndices[] = {
	// front side
	0, 1, 2,
	2, 1, 3,
	// right-side
	4, 5, 6,
	6, 5, 7,
	//back -side
	8, 9, 10,
	10, 9, 11,
	// left-side
	12, 13, 14,
	14, 13, 15,
	//top-side
	16, 17, 18,
	18, 17, 19,
	//bottom-side
	20, 21, 22,
	22, 21, 23
};

class Cube{
public:
	// Constructor
	Cube(const glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 factor = glm::vec3(1.0f));
	
	// drawing the cube
	void draw() const;
	// moving the cube around
	void translate(const glm::vec3 translateVector);
	// rotating the cube
	void rotate(const glm::vec3 rotateVector, const float radians);
	// scsale the cube
	void scale(const glm::vec3 factor);
	// get model matrix
	const glm::mat4 model() const;

private:
	// The VBO, VAO and shader ID's
	unsigned VBO=0, VAO=0, EBO=0;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

};
}

