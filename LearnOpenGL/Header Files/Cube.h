//
//  Cube.h
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 18/06/25.
//
#pragma once
#include <glm/glm.hpp>

namespace Geometry {
static const float cubeVertices[] = {
		// front side		// normals
	   -0.5f, -0.5f, 0.5f, 	0.0f, 0.0f, 1.0f,	0.0, 0.0,//front bottom-left
	   0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	1.0, 0.0,//front bottom-right
	   -0.5f, 0.5f, 0.5f, 	0.0f, 0.0f, 1.0f,	0.0, 1.0,//front top-left
	   0.5f, 0.5f, 0.5f, 	0.0f, 0.0f, 1.0f,	1.0, 1.0,//front top-right
	   
	   // right side
	   0.5f, -0.5f, 0.5f, 	1.0f, 0.0f, 0.0f,	0.0, 0.0,// right bottom-left
	   0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	1.0, 0.0,// right bottom-right
	   0.5f, 0.5f, 0.5f, 	1.0f, 0.0f, 0.0f,	0.0, 1.0,//right top-left
	   0.5f, 0.5f, -0.5f, 	1.0f, 0.0f, 0.0f,	1.0, 1.0,//right top-right
	   
	   //back side
	   0.5f, -0.5f, -0.5f, 	0.0f, 0.0f, -1.0f,	0.0, 0.0,//back bottom-left
	   -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	1.0, 0.0,//back bottom-right
	   0.5f, 0.5f, -0.5f, 	0.0f, 0.0f, -1.0f,	0.0, 1.0,//back top-left
	   -0.5f, 0.5f, -0.5f, 	0.0f, 0.0f, -1.0f,	1.0, 1.0,//back top-right
	   
	   // left side
	   -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	0.0, 0.0,//left bottom-left
	   -0.5f, -0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,	1.0, 0.0,//left bottom-right
	   -0.5f, 0.5f, -0.5f, 	-1.0f, 0.0f, 0.0f,	0.0, 1.0,//left top-left
	   -0.5f, 0.5f, 0.5f, 	-1.0f, 0.0f, 0.0f,	1.0, 1.0,//left top-right
	   
	   // top side
	   0.5f, 0.5f, -0.5f, 	0.0f, 1.0f, 0.0f,	0.0, 0.0,//top  bottom-left
	   -0.5f, 0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0, 0.0,//top bottom-right
	   0.5f, 0.5f, 0.5f, 	0.0f, 1.0f, 0.0f,	0.0, 1.0,//top top-left
	   -0.5f, 0.5f, 0.5f, 	0.0f, 1.0f, 0.0f,	1.0, 1.0,//top top-right
	   
	   // bottom side
	   0.5f, -0.5f, -0.5f, 	0.0f, -1.0f, 0.0f,	0.0, 0.0,//bottom  bottom-left
	   -0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	1.0, 0.0,//bottom bottom-right
	   0.5f, -0.5f, 0.5f, 	0.0f, -1.0f, 0.0f,	0.0, 1.0,//bottom top-left
	   -0.5f, -0.5f, 0.5f, 	0.0f, -1.0f, 0.0f,	1.0, 1.0//bottom top-right
   };
static const unsigned cubeIndices[] = {
	// front (verts 0..3)
	0, 1, 2,   2, 1, 3,
	// right (verts 4..7)
	4, 5, 6,   6, 5, 7,
	// back (verts 8..11)
	8, 9,10,  10, 9,11,
	// left (verts 12..15)
	12,13,14, 14,13,15,
	// top (verts 16..19)
	16,17,18, 18,17,19,
	// bottom (verts 20..23)
	20,21,22, 22,21,23
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
	// get world position
	const glm::vec3 position() const;
	// set absolute position
	void setOrigin(const glm::vec3 originVector);

private:
	// The VBO, VAO and shader ID's
	unsigned VBO=0, VAO=0, EBO=0;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

};
}

