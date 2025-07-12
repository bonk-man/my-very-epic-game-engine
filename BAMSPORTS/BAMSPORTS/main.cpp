#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "gl_util.h"

#include "gl_render.h"

int main(void)
{
	glfwInit();
	GLFWwindow* win = glfwCreateWindow(1280, 720, "game engine", nullptr, nullptr);

	if (!win)
	{
		std::cout << "Failed to create window!\n";
		return -1;
	}

	GLFWvidmode const* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(win, (vidmode->width - 1280) / 2, (vidmode->height - 720) / 2);

	glfwSwapInterval(1);
	glfwMakeContextCurrent(win);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initalise OpenGL\n";
		return -1;
	}

	float vertices[] =
	{
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		3, 2, 1
	};

	OpenGLRenderer::RegistrarPush("Idhi oka nandanavanam", vertices, indices, 8, 6, "default.vert", "default.frag");

	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();

		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		GL_CALL(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));

		OpenGLRenderer::Draw("Idhi oka nandanavanam");

		glfwSwapBuffers(win);
	}

	glfwDestroyWindow(win);
	glfwTerminate();
}