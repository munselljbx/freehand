#ifndef MAP_DUEL_HPP
#define MAP_DUEL_HPP

#include "IMap.hpp"

namespace map
{
class Duel : public IMap
{
public:
	Duel(sf::RenderWindow& window);
	virtual bool inArea(sf::Uint8 team, const sf::Vector2f& point) const override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture m_backgroundTex;
	mutable sf::Sprite m_background;

	sf::Vector2f m_dividerSize; // in percent of screen x, y
	sf::Color m_dividerColor;
};
}

#endif // MAP_DUEL_HPP