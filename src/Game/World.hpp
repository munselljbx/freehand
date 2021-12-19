#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include "./App/PauseMenu.hpp"
#include "InputHandler.hpp"

namespace game
{
class InputHandler;
class World
{
public:
	World(sf::RenderWindow& window);

	void gameLoop();

	bool isPaused() const;
	void pause(bool shouldPause);
	sf::RenderWindow& getWindow() const;

private:
	bool m_gamePaused = false;
	sf::RenderWindow* m_window;
	sf::Clock m_worldClock;
	bool m_exit = false;
	const double MS_PER_UPDATE = 16.66667; // Fixed time for physics update 60fps
	const int MAX_FPS = 100;
};
}

#endif // GAME_WORLD_HPP