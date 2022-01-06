#include "App.hpp"

namespace app
{
App::App(sf::RenderWindow& window)
{
	m_window = &window;
	m_systemHandle = m_window->getSystemHandle();
	m_window->create(sf::VideoMode::getDesktopMode(), "FREEHAND", sf::Style::Fullscreen);
	m_platform.setIcon(m_systemHandle);

	// Display settings
	int systemRefresh = m_platform.getRefreshRate(m_systemHandle);
	m_window->setFramerateLimit(systemRefresh);
	m_window->setKeyRepeatEnabled(false);

	if (m_cursor.loadFromSystem(sf::Cursor::Cross))
		applyCursor();
}

void App::applyCursor()
{
	m_window->setMouseCursor(m_cursor);
}

void App::run()
{
	while (m_window->isOpen())
	{
		// Start menu
		StartMenu* mainMenu = new StartMenu();
		mainMenu->run(*m_window);
		delete mainMenu;

		// Make world and loop
		map::IMap* map = new map::Duel(*m_window);
		game::World* world = new game::World(*m_window, *map, sf::Uint8(1U));
		world->gameLoop();
		delete map;
		delete world;
	}
}

sf::RenderWindow& App::getWindow() const
{
	return *m_window;
}

void App::printFullscreenModes() const
{
	// Display the list of all the video modes available for fullscreen
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
		std::cout << "Mode #" << i << ": "
				  << mode.width << "x" << mode.height << " - "
				  << mode.bitsPerPixel << " bpp" << std::endl;
	}
	// Create a window with the same pixel depth as the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::cout << "Desktop Mode: "
			  << desktop.width << "x" << desktop.height << " - "
			  << desktop.bitsPerPixel << " bpp\n"
			  << std::endl;
}
} // namespace app