#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <iostream>

#include "gl_util.h"

class OpenGLShaderProgram
{
	uint32_t m_uiProgram;
private:
	inline std::string readFile(const char* name)
	{
		std::fstream input(name);
		if (!input.good())
		{
			std::cout << "File failed to load!" << std::endl;
			exit(-1);
		}
		return std::string(
			std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>()
		);
	}
public:
	OpenGLShaderProgram(const std::string& vertex, const std::string& fragment);
	~OpenGLShaderProgram();

	void Use();
	void Unuse();
};