#include "TextureClass.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TextureClass::TextureClass(const std::string& textureName){

	int textWidth, textHeight, quantComponents;
	
	unsigned char* imageData = stbi_load((textureName).c_str(), &textWidth, &textHeight, &quantComponents, 4);

	if (imageData == NULL){

		std::cerr << "Failed to load the texture: " << textureName << std::endl;

	}

	glGenTextures(1, &textureManager);	// Quantity of textures and address of textures.
	glBindTexture(GL_TEXTURE_2D,textureManager);	// Bind the texture.
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap the texture outside the width.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap the texture outside the height.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering for when the texture is smaller than the area.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering for when the texture is larger than the area.

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textWidth, textHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); // Sending the texture to GPU.

	stbi_image_free(imageData); // Free the data from the CPU.

}

TextureClass::~TextureClass(){

	glDeleteTextures(1, &textureManager);

}

void TextureClass::BindTexture(unsigned int unit){

	assert(unit >= 0 && unit <= 31); // Check that it's working with one of the 32 textures.

	glActiveTexture(GL_TEXTURE0 + unit); // set the active texture unit.
	glBindTexture(GL_TEXTURE_2D, textureManager); // Bind the texture.

}