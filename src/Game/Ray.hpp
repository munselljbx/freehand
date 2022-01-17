#ifndef GAME_RAY_HPP
#define GAME_RAY_HPP

#include "Boundary.hpp"
#include "Helper.hpp"
#include "IActor.hpp"
#include "Map/IMap.hpp"
#include "Settings/GameSettings.hpp"

namespace game
{
class Ray : public IActor
{
public:
	Ray();
	void setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase);
	void update(const map::IMap& map);
	void advance();
	void collide(Boundary& bound);
	bool operator==(const Ray& other) const
	{
		return (IActor::operator==(other) && m_freq == other.m_freq && m_amp == other.m_amp && m_speed == other.m_speed);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	inline const static float m_MAX_HEALTH = 200.f;

	bool m_startFixed, m_endFixed; // startPoint or endPoint not moving

	float m_tPar; // sine parameter. How far ray has traveled

	float m_freq;
	float m_amp;
	float m_speed;
	float m_phase;

	sf::Vector2f m_origin;
	sf::Vector2f m_dir;
	sf::Vector2f m_start;
	sf::Vector2f m_end;

	std::vector<sf::Vector2f> m_points; // todo: O(1) removal queue but with data access?

	// collision
	size_t m_collideId;
};
} // namespace game

#endif // GAME_RAY_HPP