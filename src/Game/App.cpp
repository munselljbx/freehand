#include "App.hpp"

namespace game
{
void App::run()
{
	util::Platform platform;

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(960.0f * screenScalingFactor, 540.0f * screenScalingFactor), "FREEHAND");
	sf::WindowHandle systemHandle = window.getSystemHandle();
	platform.setIcon(systemHandle);
	// Display settings
	int systemRefresh = platform.getRefreshRate(systemHandle);
	window.setFramerateLimit(systemRefresh);
	//platform.toggleFullscreen(systemHandle, sf::Style::Fullscreen, true, window.getSize());

	// Make world and loop
	game::World world = game::World(window);
	world.gameLoop();
}
} // namespace game