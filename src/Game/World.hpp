#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include "./App/PauseMenu.hpp"
#include "./Map/IMap.hpp"
#include "ActorManager.hpp"
#include "InputHandler.hpp"
#include "Ray.hpp"

namespace game
{
class InputHandler;
class World
{
public:
	World(sf::RenderWindow& window, map::IMap& map, sf::Uint8 team);
	~World();

	void gameLoop();
	void doPause();

	bool isPaused() const;
	void pause(bool shouldPause);
	sf::RenderWindow& getWindow() const;
	ActorManager& getActorManager() const;
	map::IMap& getMap() const;
	sf::Uint8 getTeam() const;

private:
	bool m_gamePaused = false;
	sf::Clock m_worldClock;
	bool m_exit = false;
	const double MS_PER_UPDATE = 16.66667; // Fixed time for physics update 60fps
	const int MAX_FPS = 100;

	sf::RenderWindow* m_window;
	InputHandler* m_input;
	ActorManager* m_actors;
	map::IMap* m_map;

	sf::Uint8 m_localTeam;
};
}

#endif // GAME_WORLD_HPP