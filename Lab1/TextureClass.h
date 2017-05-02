#pragma once

#include <string>
#include <GL/glew.h>

class TextureClass
{
public:
	TextureClass(const std::string& textureName);
	~TextureClass();

	void BindTexture(unsigned int unit);

private:

	GLuint textureManager;

};