#include "Boundary.hpp"

namespace game
{
Boundary::Boundary() :
	IActor(sf::Uint8(0U), 0.f),
	m_line(sf::LinesStrip)
{
	sf::Vector2f nullIsland = sf::Vector2f(0.f, 0.f);
	m_line.append(sf::Vertex(nullIsland, sf::Color::White));
	m_line.append(sf::Vertex(nullIsland, sf::Color::White));
}

Boundary::Boundary(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) :
	IActor(team, health),
	m_line(sf::LinesStrip)
{
	m_line.append(sf::Vertex(startPoint, m_teamColor));
	m_line.append(sf::Vertex(endPoint, m_teamColor));
}

void Boundary::setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	m_team = team;
	m_health = health;
	m_line[0] = sf::Vertex(startPoint, m_teamColor);
	m_line[1] = sf::Vertex(endPoint, m_teamColor);
}

void Boundary::update()
{
}

void Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::cout << "d" << std::endl;
	target.draw(m_line, states);
	std::cout << m_line[0].position.x << std::endl;
	std::cout << m_line[1].position.x << std::endl;
}

}