#pragma once

#include <unordered_map>

#include <GL/glew.h>

struct Drawable
{
	unsigned int* indices;
	float* vertices;
};

class GLRenderer
{
	std::unordered_map<unsigned long, unsigned int> m_drawMap;
public:
	GLRenderer() = delete;
	~GLRenderer()
	{

	}

	void PutDrawable(unsigned long index, const struct Drawable& dw)
	{
		unsigned int count = sizeof(dw.indices);

		unsigned int vao, vbo, ibo;
		
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_TRIANGLES, sizeof(dw.vertices), dw.vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dw.indices), dw.indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	void BasicDraw(unsigned long index)
	{

	}
};