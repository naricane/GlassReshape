#include "Input.hpp"
#include <SDL3/SDL_events.h>

void
Input::handle_event(SDL_Event& event)
{
	switch (event.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			mouse_buttons_pressed[event.button.button] = true;
			mouse_buttons_pressed_once[event.button.button] = true;
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			mouse_buttons_released[event.button.button] = true;
			mouse_buttons_pressed[event.button.button] = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat) {
				keys_pressed[event.key.scancode] = true;
				keys_pressed_once[event.key.scancode] = true;
			}
			break;
		case SDL_EVENT_KEY_UP:
			keys_released[event.key.scancode] = true;
			keys_pressed[event.key.scancode] = false;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			x_relative += event.motion.xrel;
			y_relative += event.motion.yrel;
			break;
	}
}

bool
Input::is_key_pressed(int key) const
{
	return keys_pressed[key];
}

bool
Input::is_key_pressed_once(int key) const
{
	return keys_pressed_once[key];
}

bool
Input::is_key_released(int key) const
{
	return keys_released[key];
}

bool
Input::is_mouse_pressed(int button) const
{
	return mouse_buttons_pressed[button];
}

bool
Input::is_mouse_pressed_once(int button) const
{
	return mouse_buttons_pressed_once[button];
}

bool
Input::is_mouse_released(int button) const
{
	return mouse_buttons_released[button];
}

void
Input::finish_frame()
{
	for (int i = 0; i < 16; i++) {
		mouse_buttons_pressed_once[i] = false;
		mouse_buttons_released[i] = false;
	}

	for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
		keys_pressed_once[i] = false;
		keys_released[i] = false;
	}

	x_relative = 0;
	y_relative = 0;
}
