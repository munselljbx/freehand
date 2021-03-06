#ifndef GAME_IACTOR_HPP
#define GAME_IACTOR_HPP

#include "./Settings/GameSettings.hpp"
#include <SFML/Graphics.hpp>

namespace game
{
class IActor : public sf::Drawable
{ // Interface for objects which collide and are are drawn to the window
public:
	IActor(sf::Uint8 team, float health, float maxHealth)
	{
		init(team, health, maxHealth);
		inUse = false;
	}
	virtual ~IActor() = default;

	virtual sf::Uint8 getTeam()
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
		if (health <= 0.f)
			inUse = false;
	}

	bool operator==(const IActor& other) const
	{
		return (m_team == other.m_team && m_health == other.m_health && m_color == other.m_color);
	}

	bool inUse;
	bool inArea;
	bool needSend; // needs to be sent to other players

protected:
	void init(sf::Uint8 team, float health, float maxHealth)
	{
		assert(maxHealth >= health);
		assert(maxHealth >= 0.f);
		inUse = true;
		inArea = false;
		needSend = false;
		m_team = team;
		m_maxHealth = maxHealth;
		m_color = settings::GameSettings::getTeamColor(team);
		setHealth(health);
	}
	// virtual void updateCollision() = 0;
	// virtual void updateInArea() = 0;
	// virtual void onEnteredArea() = 0;
	// virtual void onExitedArea() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void updateAlpha()
	{
		if (m_maxHealth > 0.f)
		{
			if (m_health < 0.f)
			{
				m_color.a = m_MIN_ALPHA;
			}
			else
			{
				sf::Uint8 alpha = static_cast<sf::Uint8>(255.f * m_health / m_maxHealth);
				m_color.a = alpha > m_MIN_ALPHA ? alpha : m_MIN_ALPHA;
			}
		}
	}

	sf::Uint8 m_team;
	float m_health;
	float m_maxHealth;
	sf::Color m_color;
	const static sf::Uint8 m_MIN_ALPHA = 24U;
};
}

#endif // GAME_IACTOR_HPP