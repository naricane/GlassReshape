#pragma once
#include <SDL3/SDL_timer.h>

namespace gs::time {

inline double
real()
{
	return static_cast<double>(SDL_GetPerformanceCounter())
		/ static_cast<double>(SDL_GetPerformanceFrequency());
}

}
