//
//  STBDeclaration.cpp
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 09/06/25.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ProcessTexture.h"
#include <iostream>

namespace TextureFile{
GLuint processTexture(const char* filePath, FileFormat format, GLenum type){
	int width, height, nrChannels;
	GLuint texID;
	stbi_set_flip_vertically_on_load(true);

	GLubyte *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	// we need to check if the data has loaded correctly
	if (!data) {
		std::cout << "FAILED TO LOAD TEXTURE FILE FROM " << filePath << std::endl;
		return 0;
	}
	
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	// after binding we now set the parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*
	 this function has quite the # of arguments
	 
	 The first argument specifies the texture target; setting this to GL_TEXTURE_2D means this operation will generate a texture on the currently bound
	 texture object at the same target (so any textures bound to targets GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected.
	 
	 The second argument specifies the mipmap level for which we want to create a texture for if you want to set each mipmap level manually, but we'll leave
	 it at the base level which is 0.
	 
	 The third argument tells OpenGL in what kind of format we want to store the texture. Our image has only RGB values so we'll store the texture with RGB
	 values as well.
	 
	 The 4th and 5th argument sets the width and height of the resulting texture. We stored those earlier when loading the image so we'll use the
	 corresponding variables.
	 
	 Next argument should always be 0 (legacy code).
	 
	 7th and 8th argument specify the format and datatype of the source image. We loaded the image with RGB values and stored them as chars (bytes) so we'll
	 pass in the corresponding values
	 
	 Last argument is the actual data.
	 */
	switch (format){
		case FileFormat::JPG:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
			// TODO: might change this later
		case FileFormat::PNG:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			std::cout << "FILE FORMAT FOR TEXTURE NOT SPECIFIED. TEXTURE FILE LOCATED AT" << filePath << std::endl;
			return 0;
	}
	
	// we can either continue to generate mipmaps manually by incrementing the second argument
	// or let OpenGL take care of it by calling glGenerateMipmaps
	glGenerateMipmap(GL_TEXTURE_2D);
	
	// now, that we have loaded the data into the buffer, we can free the stbi_image memory
	stbi_image_free(data);
	return texID;
}
}
