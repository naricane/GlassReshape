#pragma once

#include <SDL3/SDL.h>

struct Input
{
	bool mouse_buttons_pressed_once[16] = { false };
	bool mouse_buttons_pressed[16] = { false };
	bool mouse_buttons_released[16] = { false };

	bool keys_pressed_once[SDL_SCANCODE_COUNT] = { false };
	bool keys_pressed[SDL_SCANCODE_COUNT] = { false };
	bool keys_released[SDL_SCANCODE_COUNT] = { false };

	float x_relative = 0;
	float y_relative = 0;

	void handle_event(SDL_Event& event);
	bool is_key_pressed_once(int key) const;
	bool is_key_pressed(int key) const;
	bool is_key_released(int key) const;
	bool is_mouse_pressed_once(int button) const;
	bool is_mouse_pressed(int button) const;
	bool is_mouse_released(int button) const;
	void finish_frame();
};
