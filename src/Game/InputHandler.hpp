#ifndef GAME_INPUTHANDLER_HPP
#define GAME_INPUTHANDLER_HPP

#include "./App/App.hpp"
#include "DrawControl.hpp"
#include "Settings/GameSettings.hpp"
#include "World.hpp"

namespace game
{
class World;
class InputHandler
{
public:
	InputHandler(World& world);
	~InputHandler();
	void handleInput();
	DrawControl& getDrawing();

private:
	sf::Vector2f coordToWorld(const sf::Vector2f& coordPos) const;

	void handleGainedFocus();
	void handleLostFocus();
	void handleMouseEntered();
	void handleMouseLeft();
	void handleKeyPress(sf::Event event);
	void handleMousePress(sf::Event event);
	void handleMouseRelease(sf::Event event);
	void handleTouchBegan(sf::Event event);
	void handleTouchEnded(sf::Event event);
	void handleMouseMoved(sf::Event event);
	void handleTouchMoved(sf::Event event);

	World* m_world;
	sf::RenderWindow* m_window;
	DrawControl* m_drawing;

	sf::Vector2f m_windowSize;
};
} // namespace game

#endif // GAME_INPUTHANDLER_HPP