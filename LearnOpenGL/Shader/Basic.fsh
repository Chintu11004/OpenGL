//
//  Basic.fsh
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 07/06/25.
//
#version 330 core

out vec4 FragColor;

//in vec3 vertColor;
//in vec2 texCoord;

//uniform sampler2D texture0;
//uniform sampler2D texture1;

void main(){
	//FragColor = pow(vec4(pow(texture(texture0, texCoord).rgb, vec3(2.2f)) * vertColor, 1.0f), vec4(1/2.2f));
	//FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.2f);
	FragColor = pow(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1/2.2f));
}
