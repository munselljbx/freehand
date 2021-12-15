#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include "InputHandler.hpp"

namespace game
{
class World
{
public:
	World(sf::RenderWindow& window);
	void gameLoop();

private:
	sf::RenderWindow* m_window;
	sf::Clock m_worldClock;
	bool m_worldAlive = true;
	const double MS_PER_UPDATE = 16.66667; // Fixed time for physics update 60fps
	const double MIN_MS_PER_LOOP = 4;	   // Max fps is 250
};
}

#endif // GAME_WORLD_HPP