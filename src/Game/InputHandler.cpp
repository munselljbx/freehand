#include "InputHandler.hpp"

namespace game
{

InputHandler::InputHandler(World& world)
{
	m_world = &world;
	m_drawing = new DrawControl();
	m_window = &m_world->getWindow();
}

InputHandler::~InputHandler()
{
	delete m_drawing;
}

DrawControl& InputHandler::getDrawing()
{
	return *m_drawing;
}

void InputHandler::handleInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window->close();
				break;
			case sf::Event::GainedFocus:
				handleGainedFocus();
				break;
			case sf::Event::LostFocus:
				handleLostFocus();
				break;
			case sf::Event::MouseEntered:
				handleMouseEntered();
				break;
			case sf::Event::MouseLeft:
				handleMouseLeft();
				break;
			case sf::Event::KeyPressed:
				handleKeyPress(event);
				break;
			case sf::Event::MouseButtonPressed:
				handleMousePress(event);
				break;
			case sf::Event::MouseButtonReleased:
				handleMouseRelease(event);
				break;
			case sf::Event::TouchBegan:
				handleTouchBegan(event);
				break;
			case sf::Event::TouchEnded:
				handleTouchEnded(event);
				break;
			case sf::Event::MouseMoved:
				handleMouseMoved(event);
				break;
			case sf::Event::TouchMoved:
				handleTouchMoved(event);
				break;
			default:
				break;
		}
	}
}

void InputHandler::handleGainedFocus()
{
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Cross);
	m_window->setMouseCursor(cursor);
}

void InputHandler::handleLostFocus()
{
	m_drawing->stopDraw();
}

void InputHandler::handleMouseEntered()
{
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Cross);
	m_window->setMouseCursor(cursor);
}

void InputHandler::handleMouseLeft()
{
	m_drawing->stopDraw();
}

void InputHandler::handleKeyPress(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		m_drawing->stopDraw();
		m_world->pause(true);
	}
}

void InputHandler::handleMousePress(sf::Event event)
{
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	if (mousePos.x < (float)m_window->getSize().x / 2.0f)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_drawing->startDraw();
			m_drawing->addPoint(mousePos);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			//erase
		}
	}
}

void InputHandler::handleMouseRelease(sf::Event event)
{
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		m_drawing->addPoint(mousePos);
		m_drawing->stopDraw();
	}
}

void InputHandler::handleTouchBegan(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		if (touchPos.x < (float)m_window->getSize().x / 2.)
		{
			m_drawing->startDraw();
			m_drawing->addPoint(touchPos);
		}
	}
}

void InputHandler::handleTouchEnded(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		m_drawing->addPoint(touchPos);
		m_drawing->stopDraw();
	}
}

void InputHandler::handleMouseMoved(sf::Event event)
{
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
	m_drawing->addPoint(mousePos);
}

void InputHandler::handleTouchMoved(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	m_drawing->addPoint(touchPos);
}
} // namespace game