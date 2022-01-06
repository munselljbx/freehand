#include "Boundary.hpp"

namespace game
{
Boundary::Boundary() :
	IActor(sf::Uint8(0U), 0.f, 0.f),
	m_points(2),
	m_line(sf::LinesStrip, 2)
{
	sf::Vector2f nullIsland = sf::Vector2f(0.f, 0.f);
	setLine(nullIsland, nullIsland);
}

Boundary::Boundary(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) :
	IActor(team, health, maxHealth),
	m_points(2),
	m_line(sf::LinesStrip, 2)
{
	setLine(startPoint, endPoint);
}

void Boundary::setFields(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	reInit(team, health, maxHealth);
	setLine(startPoint, endPoint);
}

void Boundary::setLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	m_points.at(0) = startPoint;
	m_points.at(1) = endPoint;
	m_line[0] = sf::Vertex(settings::GameSettings::worldToCoord(startPoint), m_teamColor);
	m_line[1] = sf::Vertex(settings::GameSettings::worldToCoord(endPoint), m_teamColor);
}

void Boundary::update()
{
}

void Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_line, states);
}

}