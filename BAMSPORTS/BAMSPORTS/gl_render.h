#pragma once

#include <GL/glew.h>

#include <unordered_map>
#include <string>

#include <iostream>

#include "gl_util.h"
#include "gl_shader.h"

typedef struct open_gl_triangle_group
{
	uint32_t vao, vbo, ibo;

	uint32_t uiVertexCount;
	uint32_t uiCount;

	OpenGLShaderProgram* shaderprogram;
} open_gl_triangle_group;

class OpenGLRenderer
{
	static std::unordered_map<std::string, open_gl_triangle_group> m_umTGRegistrar;
public:
	OpenGLRenderer() = delete;
	~OpenGLRenderer();

	static void RegistrarPush(
		const std::string& name,
		const float* fVertices,
		const unsigned int* iIndices,
		unsigned int uiVertexCount,
		unsigned int uiIndexCount,
		const std::string& vertexShader,
		const std::string& fragmentShader
	);

	static void Draw(const std::string& name);
};