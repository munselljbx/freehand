#include "Source.hpp"

namespace game
{
Source::Source() :
	IActor(sf::Uint8(0U), 0.f, 1.f)
{
}
Source::Source(sf::Uint8 team, float health, float maxHealth, float radius, sf::Vector2f pos) :
	IActor(team, health, maxHealth)
{
	pos = settings::GameSettings::worldToCoord(pos);
	radius *= settings::GameSettings::windowSize.x / settings::GameSettings::WORLD_X_MAX;
	inUse = true;

	sf::Color teamColor = settings::GameSettings::getTeamColor(m_team);
	m_outerCircle.setRadius(radius);
	m_outerCircle.setPointCount(settings::GameSettings::circleNSides(radius));
	m_outerCircle.setOrigin(radius, radius);
	m_outerCircle.setPosition(pos);
	m_outerCircle.setFillColor(teamColor);
	m_outerCircle.setOutlineThickness(-m_OUTLINE_THICKNESS);
	m_outerCircle.setOutlineColor(sf::Color::Black);

	const float innerRadius = radius * m_INNER_CIRCLE_PCT;
	const unsigned int innerPointCount = settings::GameSettings::circleNSides(innerRadius);
	m_innerCircle.setRadius(innerRadius);
	m_innerCircle.setPointCount(innerPointCount);
	m_innerCircle.setOrigin(innerRadius, innerRadius);
	m_innerCircle.setPosition(pos);
	m_innerCircle.setFillColor(sf::Color::Black);
	m_innerCircle.setOutlineThickness(m_OUTLINE_THICKNESS);
	m_innerCircle.setOutlineColor(teamColor);

	m_chalkMeter = sf::VertexArray(sf::TriangleFan, innerPointCount + 2U);
}

void Source::update(float chalk)
{
	sf::Vector2f origin = m_outerCircle.getPosition();
	sf::Color teamColor = settings::GameSettings::getTeamColor(m_team);
	m_chalkMeter[0] = sf::Vertex(origin, teamColor);
	size_t nV = m_chalkMeter.getVertexCount() - 2U;
	for (size_t i = 0; i <= nV + 1; i++)
	{
		const float chalkPct = chalk / settings::GameSettings::MAX_CHALK;
		float theta = i * 2.f * ((float)M_PI) * chalkPct / static_cast<float>(nV) + (float)M_PI_2;
		sf::Vector2f pos;
		float innerRadius = m_innerCircle.getRadius();
		pos = sf::Vector2f(innerRadius * cosf(theta), -innerRadius * sinf(theta)) + origin;
		m_chalkMeter[i + 1U] = sf::Vertex(pos, teamColor);
	}
}

void Source::setHealth(float health)
{
	IActor::setHealth(health);
	printf("Src Health: %f\n", m_health);
	m_outerCircle.setFillColor(m_color);
}

sf::Vector2f Source::getPosWorld() const
{ // position in world coords
	return settings::GameSettings::coordToWorld(m_outerCircle.getPosition());
}

float Source::getRadiusWorld() const
{ // radius in world units
	return m_outerCircle.getRadius() * settings::GameSettings::WORLD_X_MAX / settings::GameSettings::windowSize.x;
}

void Source::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_outerCircle, states);
	target.draw(m_innerCircle, states);
	target.draw(m_chalkMeter, states);
}
}