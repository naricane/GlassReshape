#include "GS/Engine/Core/Engine.hpp"

int
main()
{
	World world;
	Input input;

	Engine engine;
	engine.run(
		AppConfig{
			.start_world = world,
			.input = input,
		}
	);
}
