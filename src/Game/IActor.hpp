#ifndef GAME_IACTOR_HPP
#define GAME_IACTOR_HPP

#include "./Settings/GameSettings.hpp"
#include <SFML/Graphics.hpp>

namespace game
{
class IActor : public sf::Drawable
{ // Interface for objects which have physics updates are are drawn to the window
public:
	IActor(sf::Uint8 team, float health) :
		inUse(false),
		inArea(false),
		m_team(team),
		m_health(health),
		m_teamColor(settings::GameSettings::getTeamColor(team))
	{
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

	bool operator==(const IActor& other) const
	{
		return (m_team == other.m_team && m_health == other.m_health && m_teamColor == other.m_teamColor);
	}

	bool inUse;
	bool inArea;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	uint m_team;
	float m_health;
	sf::Color m_teamColor;
};
}

#endif // GAME_IACTOR_HPP