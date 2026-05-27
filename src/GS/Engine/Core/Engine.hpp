#pragma once

#include "GS/Engine/Render/Video.hpp"
#include "GS/Engine/World.hpp"
#include <SDL3/SDL_init.h>

struct AppConfig
{
	World start_world;
	Input input;
};

class Engine
{
private:
	Video video = unwrap(Video::make());

public:
	Engine() = default;
	~Engine() = default;

	void run(AppConfig&& config);
};
