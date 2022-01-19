#ifndef GAME_SOURCE_HPP
#define GAME_SOURCE_HPP

#include "./Settings/GameSettings.hpp"
#include "IActor.hpp"

namespace game
{
class Source : public IActor
{
public:
	Source();
	Source(sf::Uint8 team, float health, float maxHealth, float radius, sf::Vector2f pos);
	void update(float chalk);
	virtual void setHealth(float health) override;
	sf::Vector2f getPosWorld() const;
	float getRadiusWorld() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::CircleShape m_outerCircle;
	sf::CircleShape m_innerCircle;
	sf::VertexArray m_chalkMeter;

	inline const static float m_INNER_CIRCLE_PCT = 0.7f;
	inline const static float m_OUTLINE_THICKNESS = 3.f;
};
}

#endif // GAME_SOURCE_HPP