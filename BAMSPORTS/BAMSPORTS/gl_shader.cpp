#include "gl_shader.h"

OpenGLShaderProgram::OpenGLShaderProgram(const std::string& vertex, const std::string& fragment)
{
	uint32_t vxsid = glCreateShader(GL_VERTEX_SHADER);
	uint32_t frgid = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vxsf = readFile(vertex.c_str());
	std::string fgsf = readFile(fragment.c_str());

	const char* temp = vxsf.c_str();

	GL_CALL(glShaderSource(vxsid, 1, &temp, 0));
	temp = fgsf.c_str();
	GL_CALL(glShaderSource(frgid, 1, &temp, 0));
	GL_CALL(glCompileShader(vxsid));
	GL_CALL(glCompileShader(frgid));
	
	m_uiProgram = glCreateProgram();
	GL_CALL(glAttachShader(m_uiProgram, vxsid));
	GL_CALL(glAttachShader(m_uiProgram, frgid));
	GL_CALL(glLinkProgram(m_uiProgram));
	GL_CALL(glValidateProgram(m_uiProgram));

	GL_CALL(glDeleteShader(vxsid));
	GL_CALL(glDeleteShader(frgid));
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
	GL_CALL(glDeleteProgram(m_uiProgram));
}

void OpenGLShaderProgram::Use()
{
	GL_CALL(glUseProgram(m_uiProgram));
}

void OpenGLShaderProgram::Unuse()
{
	GL_CALL(glUseProgram(0));
}
