#include "Engine.hpp"
#include "GS/Engine/Core/Time.hpp"

void
Engine::run(AppConfig&& config)
{
	bool running = true;
	SDL_Event event;

	const double dt = 1.0 / 60;

	double current_time = gs::time::real();
	double accumulator = 0.0;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
			if (event.type == SDL_EVENT_WINDOW_RESIZED) {
				GLCall(glViewport(0, 0, event.window.data1, event.window.data2));
			}
			config.input.handle_event(event);
			config.start_world.handle_event(event);
		}

		double new_time = gs::time::real();
		double frame_time = new_time - current_time;
		current_time = new_time;
		accumulator += frame_time;

		config.start_world.update(config.input);
		config.input.finish_frame();

		while (accumulator >= dt) {

			config.start_world.physics_update();
			accumulator -= dt;
		}

		GLCall(glEnable(GL_DEPTH_TEST));

		video::clear();
		const float alpha = accumulator / dt;
		config.start_world.draw(video, alpha);
		video::display(video);
	}
}
