#include "gl_render.h"

std::unordered_map<std::string, open_gl_triangle_group> OpenGLRenderer::m_umTGRegistrar;

OpenGLRenderer::~OpenGLRenderer()
{
	for (auto const& [name, group] : m_umTGRegistrar)
	{
		delete group.shaderprogram;
		GL_CALL(glDeleteVertexArrays(1, &group.vao));
		GL_CALL(glDeleteBuffers(1, &group.vbo));
		GL_CALL(glDeleteBuffers(1, &group.ibo));
	}
}

void OpenGLRenderer::RegistrarPush(const std::string& name, const float* fVertices, const unsigned int* iIndices, unsigned int uiVertexCount, unsigned int uiIndexCount, const std::string& vertexShader, const std::string& fragmentShader)
{
	if (m_umTGRegistrar.find(name) != m_umTGRegistrar.end())
	{
		throw std::runtime_error("This object already exists!\n");
	}

	open_gl_triangle_group gr;

	gr.uiVertexCount = uiVertexCount;
	gr.uiCount = uiIndexCount;

	GL_CALL(glGenVertexArrays(1, &gr.vao));

	uint32_t vbo;
	GL_CALL(glGenBuffers(1, &vbo));
	gr.vbo = vbo;
	uint32_t ibo;
	GL_CALL(glGenBuffers(1, &ibo));
	gr.ibo = ibo;

	GL_CALL(glBindVertexArray(gr.vao));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, uiVertexCount * sizeof(float), fVertices, GL_STATIC_DRAW));

	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0));

	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, gr.uiCount * sizeof(unsigned int), iIndices, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL_CALL(glBindVertexArray(0));

	gr.shaderprogram = new OpenGLShaderProgram(vertexShader, fragmentShader);

	m_umTGRegistrar[name] = gr;
}

void OpenGLRenderer::Draw(const std::string& name)
{
	if (m_umTGRegistrar.find(name) == m_umTGRegistrar.end())
	{
		throw std::runtime_error("This name does not exist\n");
	}

	m_umTGRegistrar[name].shaderprogram->Use();
	GL_CALL(glBindVertexArray(m_umTGRegistrar[name].vao));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_umTGRegistrar[name].ibo));
	GL_CALL(glDrawElements(GL_TRIANGLES, m_umTGRegistrar[name].uiCount, GL_UNSIGNED_INT, (const void*)0));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL_CALL(glBindVertexArray(0));
	m_umTGRegistrar[name].shaderprogram->Unuse();
}
