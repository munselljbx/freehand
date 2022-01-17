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
	void setFields(sf::Uint8 team, float health, float maxHealth, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	void setLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
	sf::Vector2f getStart() const;
	sf::Vector2f getEnd() const;
	virtual void setHealth(float health) override;
	bool operator==(const Boundary& other) const
	{
		return (IActor::operator==(other) && m_line.getBounds() == other.m_line.getBounds());
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateGraphic();

	sf::Vector2f m_start;
	sf::Vector2f m_end;
	sf::VertexArray m_line; // for drawing. two vertices: [0] is startpoint of line [1] end.
};
} // namespace game

#endif // GAME_BOUNDARY_HPP