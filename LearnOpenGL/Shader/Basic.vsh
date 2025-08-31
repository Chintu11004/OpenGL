//
//  Basic.vsh
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 07/06/25.
//
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

//out vec3 vertColor;
//out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(view * model * vec4(aPos, 1.0f));
	//Normal = mat3(transpose(inverse(view * model))) * aNormal;
	Normal = mat3(view * model) * aNormal;
	//ViewLightPos =
	//vertColor = aColor;
	texCoord = aTexCoord;
}
