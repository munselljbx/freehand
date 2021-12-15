#include "InputHandler.hpp"

namespace game
{
void InputHandler::handleInput(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				handleKeyPress(event);
				break;
			case sf::Event::MouseButtonPressed:
				handleMousePress(event, window);
				break;
			case sf::Event::MouseButtonReleased:
				handleMouseRelease(event, window);
				break;
			case sf::Event::TouchBegan:
				handleTouchBegan(event, window);
				break;
			case sf::Event::TouchEnded:
				handleTouchEnded(event, window);
				break;
			case sf::Event::MouseMoved:
				handleMouseMoved(event, window);
				break;
			case sf::Event::TouchMoved:
				handleTouchMoved(event, window);
				break;
			default:
				break;
		}
	}
}

void InputHandler::handleKeyPress(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		// togglePause
	}
}

void InputHandler::handleMousePress(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	if (mousePos.x < (float)window.getSize().x / 2.0f)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			drawing->startDraw();
			drawing->addPoint(mousePos);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			//erase
		}
	}
}

void InputHandler::handleMouseRelease(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		drawing->addPoint(mousePos);
		drawing->stopDraw();
	}
}

void InputHandler::handleTouchBegan(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f touchPos = window.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		if (touchPos.x < (float)window.getSize().x / 2.)
		{
			drawing->startDraw();
			drawing->addPoint(touchPos);
		}
	}
}

void InputHandler::handleTouchEnded(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f touchPos = window.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		drawing->addPoint(touchPos);
		drawing->stopDraw();
	}
}

void InputHandler::handleMouseMoved(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
	drawing->addPoint(mousePos);
}

void InputHandler::handleTouchMoved(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f touchPos = window.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	drawing->addPoint(touchPos);
}
} // namespace game