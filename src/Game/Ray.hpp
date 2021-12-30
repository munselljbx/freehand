#ifndef GAME_RAY_HPP
#define GAME_RAY_HPP

#include "IActor.hpp"

namespace game
{
class Ray : public IActor
{
public:
	Ray();
	Ray(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, const sf::Vector2f& velocity);
	void setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, const sf::Vector2f& velocity);
	virtual void update();

	bool operator==(const Ray& other) const
	{
		return (IActor::operator==(other) && m_freq == other.m_freq && m_amp == other.m_amp && m_vel == other.m_vel);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float m_freq;
	float m_amp;

	sf::Vector2f m_vel;
	sf::Vector2f m_start;
	sf::Vector2f m_end;

	sf::VertexArray m_lines;
};
} // namespace game

#endif // GAME_RAY_HPP