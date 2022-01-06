#ifndef GAME_DRAWCONTROL_HPP
#define GAME_DRAWCONTROL_HPP

#include "ActorManager.hpp"
#include "Boundary.hpp"
#include "Helper.hpp"
#include "Pool.hpp"
#include "Ray.hpp"
#include <pocketfft-cpp/pocketfft_hdronly.h>

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

	bool evaluateData() const;
	bool evaluateLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float meanErr) const;
	bool evaluateSine(float mRise, float mRun, const sf::Vector2f& origin, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) const;

	ActorManager* m_actors;

	bool m_isDrawing = false;
	std::vector<sf::Vector2f> m_points;
	inline const static float m_DOT_RADIUS_DEFAULT = 7.0f;
	inline const static unsigned int m_DOT_POINTCOUNT_DEFAULT = 20U;
	mutable sf::CircleShape m_dot;
	inline const static unsigned int m_MIN_POINTS = 15U;
	inline const static float m_MAX_LINE_ERR = 30.f;

	// Boundary reqs
	inline const static float m_MIN_BOUNDARY_LENGTH = 10.f;
	inline const static float m_MAX_BOUNDARY_LENGTH = 200.f;

	// Ray reqs //todo: check these
	inline const static float m_MIN_RAY_LENGTH = 10.f;
	inline const static float m_MAX_RAY_LENGTH = 200.f;
	inline const static unsigned int m_MIN_RAY_CYCLES = 1U;
	inline const static unsigned int m_MAX_RAY_CYCLES = 10U;
	inline const static float m_MIN_RAY_AMPLITUDE = 10.f;
	inline const static float m_MAX_RAY_AMPLITUDE = 100.f;
};
} // namespace game

#endif // GAME_DRAWCONTROL_HPP