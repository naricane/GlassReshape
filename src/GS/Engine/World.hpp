#pragma once

#include "GS/Engine/Core/Input.hpp"
#include "GS/Engine/Render/Video.hpp"

struct World
{
	World();
	void handle_event(SDL_Event& event);
	void update(const Input& input);
	void physics_update();
	void draw(const Video& video, const float alpha);
};
