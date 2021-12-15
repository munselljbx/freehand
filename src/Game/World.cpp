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
	InputHandler input;

	sf::Int32 previous = m_worldClock.getElapsedTime().asMilliseconds();
	sf::Int32 lag = 0;
	while (m_window->isOpen() && m_worldAlive)
	{
		sf::Int32 current = m_worldClock.getElapsedTime().asMilliseconds();
		sf::Int32 elapsed = current - previous;

		previous = current;
		lag += elapsed;

		// Input handling
		input.handleInput(*m_window);

		//Fixed Time Loop
		while (lag >= MS_PER_UPDATE)
		{

			//For gameloop DO NOT TOUCH
			lag -= MS_PER_UPDATE;
		}

		//Render
		m_window->clear();
		m_window->draw(*input.getDrawing());
		m_window->display();
	}
}
} // namespace game