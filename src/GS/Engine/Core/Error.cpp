#include "Error.hpp"
#include <glad/glad.h>

namespace error {

void
clear_gl_error()
{
	while (glGetError() != GL_NO_ERROR)
		;
}

void
log_gl_error(const char* function, const char* file, int line)
{
	while (GLenum error_code = glGetError()) {
		std::string error;
		switch (error_code) {
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
		}
		std::cerr << std::format("[OpenGL Error] ({}): {} {} {}", error, function, file, line)
				  << "\n";
	}
}

}
