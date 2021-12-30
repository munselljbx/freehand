#ifndef GAME_BOUNDARY_HPP
#define GAME_BOUNDARY_HPP

#include "IActor.hpp"

namespace game
{
class Boundary : public IActor
{
public:
	Boundary();
	Boundary(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	void setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	virtual void update();

	bool operator==(const Boundary& other) const
	{
		return (IActor::operator==(other) && m_line.getBounds() == other.m_line.getBounds());
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray m_line; // two vertices: [0] is startpoint of line [1] end.
};
} // namespace game

#endif // GAME_BOUNDARY_HPP