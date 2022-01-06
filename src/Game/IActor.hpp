#ifndef GAME_IACTOR_HPP
#define GAME_IACTOR_HPP

#include "./Settings/GameSettings.hpp"
#include <SFML/Graphics.hpp>

namespace game
{
class IActor : public sf::Drawable
{ // Interface for objects which have physics updates are are drawn to the window
public:
	IActor(sf::Uint8 team, float health, float maxHealth) :
		inUse(false),
		inArea(false),
		m_team(team),
		m_health(health),
		m_maxHealth(maxHealth),
		m_teamColor(settings::GameSettings::getTeamColor(team))
	{
		updateAlpha();
	}
	virtual ~IActor() = default;
	virtual void update() = 0;

	virtual float getTeam()
	{
		return m_team;
	}
	virtual float getHealth()
	{
		return m_health;
	}
	virtual void setHealth(float health)
	{
		m_health = health;
		updateAlpha();
	}

	bool operator==(const IActor& other) const
	{
		return (m_team == other.m_team && m_health == other.m_health && m_teamColor == other.m_teamColor);
	}

	bool inUse;
	bool inArea;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void updateAlpha()
	{
		sf::Uint8 alpha = static_cast<sf::Uint8>(255.f * m_health / m_maxHealth);
		m_teamColor.a = alpha > m_MIN_ALPHA ? alpha : m_MIN_ALPHA;
	}

	sf::Uint8 m_team;
	float m_health;
	float m_maxHealth;
	sf::Color m_teamColor;
	const static sf::Uint8 m_MIN_ALPHA = 50U;
};
}

#endif // GAME_IACTOR_HPP