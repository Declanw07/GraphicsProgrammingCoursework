#include <fstream>
#include <iostream>
#include "ShaderClass.h"

Shader::Shader(const std::string& shaderName){

	shaderProgram = glCreateProgram();

	shaders[0] = initShader(LoadShader("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = initShader(LoadShader("C:\\Users\\declan\\Desktop\\GraphicsProgCoursework\\res\\shader.frag"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < SHADER_QUANTITY; i++)
	{
		glAttachShader(shaderProgram, shaders[i]);
	}

	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "textCoordinate");

	glLinkProgram(shaderProgram);
	ShaderExceptionCheck(shaderProgram, GL_VALIDATE_STATUS, true, "ERROR: Shader program is not valid.");

	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderProgram, "transform");

}

GLuint Shader::initShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	ShaderExceptionCheck(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

Shader::~Shader(){

	for (unsigned int i = 0; i < SHADER_QUANTITY; i++)
	{
		glDetachShader(shaderProgram, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(shaderProgram);

}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::BindShader(){

	glUseProgram(shaderProgram);

}

void Shader::ShaderExceptionCheck(GLuint shader, GLuint flag, bool isProgram, const std::string& exception){

	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram){

		glGetProgramiv(shader, flag, &success);

	}else{

		glGetShaderiv(shader, flag, &success);

	}

	if (success == GL_FALSE){

		if (isProgram){

			glGetProgramInfoLog(shader, sizeof(error), NULL, error);

		}else{

			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		}

		std::cerr << exception << ": " << error << "" << std::endl;

	}
}

void Shader::Update(const Transform& transform){

	glm::mat4 model = transform.fetchModel(); // Fetch the model matrix
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &model[0][0]);

}