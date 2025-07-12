#pragma once

#define GL_CALL(x) do { x; GLenum error = glGetError(); while (error != GL_NO_ERROR) { std::cout << "OpenGL Error" << error << " in " << #x << " at " << __FILE__ << ":" << __LINE__ << "\n"; error = glGetError(); } } while(0)