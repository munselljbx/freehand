#ifndef GAME_DRAWCONTROL_HPP
#define GAME_DRAWCONTROL_HPP

#include "ActorManager.hpp"
#include "Boundary.hpp"
#include "Pool.hpp"
#include "Ray.hpp"
#include "helper.hpp"

namespace game
{
class DrawControl : public sf::Drawable
{
public:
	DrawControl(ActorManager& actors) :
		m_actors(&actors),
		m_dot(m_DOT_RADIUS_DEFAULT, m_DOT_POINTCOUNT_DEFAULT) {};
	DrawControl(ActorManager& actors, float dotRadius, int dotPointCount) :
		m_actors(&actors),
		m_dot(dotRadius, dotPointCount) {};
	void startDraw();
	void stopDraw();
	void addPoint(const sf::Vector2f& pos);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool evaluateLine();
	bool evaluateSine();

	ActorManager* m_actors;

	bool m_isDrawing = false;
	std::vector<sf::Vector2f> m_points;
	const float m_DOT_RADIUS_DEFAULT = 7.0f;
	const unsigned int m_DOT_POINTCOUNT_DEFAULT = 20U;
	mutable sf::CircleShape m_dot;
	const unsigned int m_MIN_POINTS = 15U;
};
} // namespace game

#endif // GAME_DRAWCONTROL_HPP