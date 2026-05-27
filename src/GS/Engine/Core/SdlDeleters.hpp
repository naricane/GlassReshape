#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <memory>

namespace sdl {

template<auto DestroyFn>
struct sdl_deleter
{
	template<typename T>
	void operator()(T* ptr) const
	{
		if (ptr) {
			DestroyFn(ptr);
		}
	}
};

struct gl_context_deleter
{
	void operator()(SDL_GLContext ctx) const
	{
		if (ctx) {
			SDL_GL_DestroyContext(ctx);
		}
	}
};

using window = std::unique_ptr<SDL_Window, sdl_deleter<SDL_DestroyWindow>>;
using context = std::unique_ptr<std::remove_pointer_t<SDL_GLContext>, gl_context_deleter>;

}
