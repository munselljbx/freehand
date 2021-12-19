#include "App.hpp"

namespace app
{
App::App(sf::RenderWindow& window)
{
	m_window = &window;
	m_systemHandle = m_window->getSystemHandle();
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = m_platform.getScreenScalingFactor(m_systemHandle);
	// Use the screenScalingFactor
	m_window->create(sf::VideoMode(960.0f * screenScalingFactor, 540.0f * screenScalingFactor), "FREEHAND");
	m_platform.setIcon(m_systemHandle);
	// Display settings
	int systemRefresh = m_platform.getRefreshRate(m_systemHandle);
	m_window->setFramerateLimit(systemRefresh);
	//platform.toggleFullscreen(systemHandle, sf::Style::Fullscreen, true, window.getSize());

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
		StartMenu* mainMenu = new StartMenu();
		mainMenu->run(*m_window);
		delete mainMenu;
		// Make world and loop
		game::World* world = new game::World(*m_window);
		world->gameLoop();
		delete world;
	}
}

sf::RenderWindow& App::getWindow() const
{
	return *m_window;
}

} // namespace app