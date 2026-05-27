#include "Video.hpp"
#include "GS/Engine/Core/SdlDeleters.hpp"
#include <glad/glad.h>

std::expected<Video, error::ErrorMessage>
Video::make()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return std::unexpected(error::ErrorMessage{ SDL_GetError() });
	}

	sdl::window window(
		SDL_CreateWindow("Game", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)
	);

	if (!window) {
		return std::unexpected(error::ErrorMessage{ SDL_GetError() });
	}
	SDL_SetWindowRelativeMouseMode(window.get(), true);

	sdl::context context(SDL_GL_CreateContext(window.get()));
	if (!context) {
		return std::unexpected(error::ErrorMessage{ SDL_GetError() });
	}

	if (!gladLoadGLLoader(GLADloadproc(SDL_GL_GetProcAddress))) {
		return std::unexpected(error::ErrorMessage{ "Failed to initialize GLAD!" });
	}

	return Video(std::move(window), std::move(context));
}

Video::Video(sdl::window window, sdl::context context)
	: window(std::move(window))
	, context(std::move(context))
{
}

namespace video {

void
clear()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.4f, 1.f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void
display(const Video& v)
{
	SDL_GL_SwapWindow(v.window.get());
}

void
draw(const Mesh& mesh, const Shader& shader)
{
	shader.use();
	mesh.bind();
	glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr);
}

void
draw(const DrawMeshes& command, const Shader& shader)
{
}

}
