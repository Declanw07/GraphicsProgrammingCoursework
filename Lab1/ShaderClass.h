#pragma once
#include <GL/glew.h>
#include <string>
#include "TransformClass.h"

class Shader
{
public:

	Shader(const std::string& shaderName);
	~Shader();

	void BindShader();
	std::string Shader::LoadShader(const std::string& shaderName);
	void Shader::ShaderExceptionCheck(GLuint shader, GLuint flag, bool isProgram, const std::string& exception);
	GLuint Shader::initShader(const std::string& text, unsigned int type);

	void Update(const Transform& Transform);

private:

	static const unsigned int SHADER_QUANTITY = 2;

	enum{
	
		TRANSFORM_U,
		UNIFORM_QUANTITY

	};

	//Shader(const Shader& other){}
	//void operator=(const Shader& other){}

	GLuint shaderProgram;
	GLuint shaders[SHADER_QUANTITY];
	GLuint uniforms[UNIFORM_QUANTITY];

};