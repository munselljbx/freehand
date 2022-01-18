#include "Boundary.hpp"

namespace game
{
Boundary::Boundary() :
	IActor(sf::Uint8(0U), 0.f, 0.f),
	m_start(0.f, 0.f),
	m_end(0.f, 0.f),
	m_line(sf::LinesStrip, 2)
{
	sf::Vector2f nullIsland = sf::Vector2f(0.f, 0.f);
	setLine(nullIsland, nullIsland);
}

void Boundary::setFields(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	IActor::init(team, health, maxHealth);
	setLine(startPoint, endPoint);
}

void Boundary::setLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	m_start = startPoint;
	m_end = endPoint;
	m_line[0] = sf::Vertex(settings::GameSettings::worldToCoord(startPoint), m_color);
	m_line[1] = sf::Vertex(settings::GameSettings::worldToCoord(endPoint), m_color);
}

sf::Vector2f Boundary::getStart() const
{
	return m_start;
}
sf::Vector2f Boundary::getEnd() const
{
	return m_end;
}

void Boundary::setHealth(float health)
{
	IActor::setHealth(health);
	updateGraphicColor();
}

void Boundary::updateGraphicColor()
{
	std::cout << m_color.a << std::endl;
	m_line[0].color = m_color;
	m_line[1].color = m_color;
}

void Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_line, states);
}

}