//
//  ProcessTexture.h
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 09/06/25.
//
#pragma once

#include <glad/glad.h>

namespace TextureFile{

// this enum class helps differentitate between the various formats the textures may come in
enum class FileFormat : uint8_t{
	JPG, PNG
};

// This struct stores the filePath, and the format of the texture file that will be used
struct TextureLocation {
	const char* filePath;
	FileFormat format;
	GLenum type;
};

// processes the texture file at the specified path, and returns a texID
// for that texture, if it has succesfully been created and processed
GLuint processTexture(const char* filePath, FileFormat format, GLenum type);
}
