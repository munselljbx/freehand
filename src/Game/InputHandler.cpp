#include "InputHandler.hpp"

namespace game
{
InputHandler::InputHandler(World& world)
{
	m_world = &world;
	m_window = &m_world->getWindow();
	m_drawing = new DrawControl(m_world->getActorManager());
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

sf::Vector2f InputHandler::coordToWorld(const sf::Vector2f& coordPos) const
{ // coord is sfml coords -- top left origin and top right of window is window size
	// world is bottom left origin and top right of window is (WORLD_X_MAX, WORLD_Y_MAX)
	sf::Vector2f windowSize = m_window->mapPixelToCoords(static_cast<sf::Vector2i>(m_window->getSize()));
	sf::Vector2f worldPos;
	worldPos.x = (windowSize.x - coordPos.x) * (settings::GameSettings::WORLD_X_MAX / windowSize.x);
	worldPos.y = (windowSize.y - coordPos.y) * (settings::GameSettings::WORLD_Y_MAX / windowSize.y);
	return worldPos;
}

void InputHandler::handleGainedFocus()
{
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Cross);
	m_window->setMouseCursor(cursor);

	//m_window->setMouseCursorGrabbed(true);
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
	if (m_world->getMap().inArea(m_world->getTeam(), mousePos))
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_drawing->startDraw();
			m_drawing->addPoint(coordToWorld(mousePos));
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
		m_drawing->addPoint(coordToWorld(mousePos));
		m_drawing->stopDraw();
	}
}

void InputHandler::handleTouchBegan(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		if (m_world->getMap().inArea(m_world->getTeam(), touchPos))
		{
			m_drawing->startDraw();
			m_drawing->addPoint(coordToWorld(touchPos));
		}
	}
}

void InputHandler::handleTouchEnded(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (event.touch.finger == 0)
	{
		m_drawing->addPoint(coordToWorld(touchPos));
		m_drawing->stopDraw();
	}
}

void InputHandler::handleMouseMoved(sf::Event event)
{
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
	if (m_world->getMap().inArea(m_world->getTeam(), mousePos))
	{
		m_drawing->addPoint(coordToWorld(mousePos));
	}
	else
	{
		m_drawing->stopDraw();
	}
}

void InputHandler::handleTouchMoved(sf::Event event)
{
	sf::Vector2f touchPos = m_window->mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y));
	if (m_world->getMap().inArea(m_world->getTeam(), touchPos))
	{
		m_drawing->addPoint(coordToWorld(touchPos));
	}
	else
	{
		m_drawing->stopDraw();
	}
}
} // namespace game