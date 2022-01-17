#include "Source.hpp"

namespace game
{
Source::Source(sf::Uint8 team, float health, float maxHealth, float radius, sf::Vector2f pos, float chalk) : IActor(team, health, maxHealth)
{
	inUse = true;
	m_outerCircle = sf::CircleShape(radius, pointCount = , m_teamColor);
}

void Source::update(float chalk)
{

}

void Source::draw(sf::RenderTarget& target, sf::RenderStates states) const override
{
	target.draw(m_outerCircle, states);
	target.draw(m_innerCircle, states);
	target.draw(m_chalkMeter, states);
}
}