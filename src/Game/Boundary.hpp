#ifndef GAME_BOUNDARY_HPP
#define GAME_BOUNDARY_HPP

#include "Helper.hpp"
#include "IActor.hpp"
#include "Settings/GameSettings.hpp"

namespace game
{
class Boundary : public IActor
{
public:
	Boundary();
	Boundary(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	void setFields(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	void setLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);

	virtual void update();

	bool operator==(const Boundary& other) const
	{
		return (IActor::operator==(other) && m_line.getBounds() == other.m_line.getBounds());
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<sf::Vector2f> m_points; // two points
	sf::VertexArray m_line;				// for drawing. two vertices: [0] is startpoint of line [1] end.
};
} // namespace game

#endif // GAME_BOUNDARY_HPP