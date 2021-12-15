#ifndef GAME_INPUTHANDLER_HPP
#define GAME_INPUTHANDLER_HPP

#include "DrawControl.hpp"
#include "PCH.hpp"

namespace game
{
class InputHandler
{
public:
	~InputHandler()
	{
		delete drawing;
	}
	void handleInput(sf::RenderWindow& window);
	DrawControl* getDrawing() const
	{
		return drawing;
	};

private:
	void handleKeyPress(sf::Event event);
	void handleMousePress(sf::Event event, sf::RenderWindow& window);
	void handleMouseRelease(sf::Event event, sf::RenderWindow& window);
	void handleTouchBegan(sf::Event event, sf::RenderWindow& window);
	void handleTouchEnded(sf::Event event, sf::RenderWindow& window);
	void handleMouseMoved(sf::Event event, sf::RenderWindow& window);
	void handleTouchMoved(sf::Event event, sf::RenderWindow& window);

	DrawControl* drawing = new DrawControl();
};
}

#endif