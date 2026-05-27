#pragma once

#include "GS/Engine/Core/Error.hpp"
#include "GS/Engine/Core/SdlDeleters.hpp"
#include "GS/Engine/Render/Mesh.hpp"
#include "GS/Engine/Render/Shader.hpp"

struct Video
{
	sdl::window window;
	sdl::context context;
	static std::expected<Video, error::ErrorMessage> make();

private:
	Video(sdl::window window, sdl::context context);
};

namespace video {

struct DrawMeshes
{
	// TODO
};

void
clear();

void
display(const Video& video);

void
draw(const Mesh& mesh, const Shader& shader);

void
draw(const DrawMeshes& command, const Shader& shader, const glm::mat4& view_proj);

}
