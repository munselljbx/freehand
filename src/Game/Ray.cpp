#include "Ray.hpp"

namespace game
{
Ray::Ray() :
	IActor(sf::Uint8(0U), 0.f)
{
}
Ray::Ray(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, const sf::Vector2f& velocity) :
	IActor(team, health)
{
	m_start = startPoint;
	m_end = endPoint;
	m_freq = frequency;
	m_amp = amplitude;
	m_vel = velocity;
}

void Ray::setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, const sf::Vector2f& velocity)
{
	m_team = team;
	m_health = health;
	m_start = startPoint;
	m_end = endPoint;
	m_freq = frequency;
	m_amp = amplitude;
	m_vel = velocity;
}

void Ray::update()
{
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// update vertex array of lines to display ray
	target.draw(m_lines, states);
}
}