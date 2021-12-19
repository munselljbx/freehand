#ifndef GAME_DRAWCONTROL_HPP
#define GAME_DRAWCONTROL_HPP

#include "PCH.hpp"

namespace game
{
class DrawControl : public sf::Drawable
{
public:
	DrawControl() :
		m_dot(m_DOT_RADIUS_DEFAULT, m_DOT_POINTCOUNT_DEFAULT) {};
	DrawControl(float dotRadius, int dotPointCount) :
		m_dot(dotRadius, dotPointCount) {};
	void startDraw();
	void stopDraw();
	void addPoint(const sf::Vector2f& pos);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool m_isDrawing = false;
	std::vector<sf::Vector2f> m_points;
	const float m_DOT_RADIUS_DEFAULT = 7.0f;
	const int m_DOT_POINTCOUNT_DEFAULT = 20;
	mutable sf::CircleShape m_dot;
};
} // namespace game

#endif // GAME_DRAWCONTROL_HPP