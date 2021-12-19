#include "World.hpp"

namespace game
{
World::World(sf::RenderWindow& window)
{
	m_window = &window;
}

void World::gameLoop()
{
	//Setup
	InputHandler input = InputHandler(*this);

	sf::Int32 previous = m_worldClock.getElapsedTime().asMilliseconds();
	sf::Int32 lag = 0;
	while (m_window->isOpen() && !m_exit)
	{
		sf::Int32 current = m_worldClock.getElapsedTime().asMilliseconds();
		sf::Int32 elapsed = current - previous;

		previous = current;
		lag += elapsed;

		// Input handling
		input.handleInput();

		//Fixed Time Loop
		while (lag >= MS_PER_UPDATE)
		{

			//For gameloop DO NOT TOUCH
			lag -= MS_PER_UPDATE;
		}

		//Render
		m_window->clear();
		m_window->draw(input.getDrawing());
		m_window->display();

		if (isPaused())
		{ //Enter Pause loop
			sf::Texture windowContentTexture;
			sf::Vector2u windowSize = m_window->getSize();
			windowContentTexture.create(windowSize.x, windowSize.y);
			windowContentTexture.update(*m_window);
			app::PauseMenu* gamePauseMenu = new app::PauseMenu(windowContentTexture);
			gamePauseMenu->run(*m_window);
			delete gamePauseMenu;

			m_gamePaused = false;
			m_window->setFramerateLimit(MAX_FPS);
		}
	}
}

bool World::isPaused() const
{
	return m_gamePaused;
}

void World::pause(bool shouldPause)
{
	m_gamePaused = shouldPause;
}

sf::RenderWindow& World::getWindow() const
{
	return *m_window;
}

} // namespace game