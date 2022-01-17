#ifndef GAME_SOURCE_HPP
#define GAME_SOURCE_HPP

#include "./Settings/GameSettings.hpp"

namespace game
{
class Source : public IActor
{
public:
	Source(sf::Uint8 team, float health, float maxHealth, float chalk);
	void update(float chalk);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::CircleShape m_outerCircle;
	sf::CircleShape m_innerCircle;
	sf::VertexArray m_chalkMeter;
}

}

#endif // GAME_SOURCE_HPP