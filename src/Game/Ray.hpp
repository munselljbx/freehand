#ifndef GAME_RAY_HPP
#define GAME_RAY_HPP

#include "Boundary.hpp"
#include "Helper.hpp"
#include "IActor.hpp"
#include "Map/IMap.hpp"
#include "Settings/GameSettings.hpp"
#include "Source.hpp"

namespace game
{
class Ray : public IActor
{
public:
	Ray();
	void setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase, bool reflecting = false);
	void update(const map::IMap& map);
	void advance();

	virtual void setHealth(float health) override;

	float getHealthPerLength() const;
	float getTPar() const;
	float getFrequency() const;
	float getAmplitude() const;
	float getSpeed() const;
	float getPhase() const;
	sf::Vector2f getDirection() const;
	sf::Vector2f getStart() const;
	sf::Vector2f getEnd() const;
	bool operator==(const Ray& other) const
	{
		return (IActor::operator==(other) && m_freq == other.m_freq && m_amp == other.m_amp && m_speed == other.m_speed);
	}

	bool startFixed, endFixed; // startPoint or endPoint not moving
	bool collisionFrame;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	inline const static float m_MAX_HEALTH = 200.f;

	float m_healthPerLength;

	float m_tPar; // sine parameter. How far ray has traveled

	float m_freq;
	float m_amp;
	float m_speed;
	float m_phase;

	sf::Vector2f m_origin;
	sf::Vector2f m_dir;
	sf::Vector2f m_start;
	sf::Vector2f m_end;

	unsigned int m_freezeStartSteps;

	std::vector<sf::Vector2f> m_points; // todo: O(1) removal queue but with data access?
};
} // namespace game

#endif // GAME_RAY_HPP