#include "Ray.hpp"

namespace game
{
Ray::Ray() :
	IActor(sf::Uint8(0U), 0.f)
{
}
Ray::Ray(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase) :
	IActor(team, health),
	m_startFixed(true),
	m_endFixed(false),
	m_tPar(0.f),
	m_freq(frequency),
	m_amp(amplitude),
	m_speed(speed),
	m_phase(phase),
	m_origin(startPoint.x, startPoint.y),
	m_dir(sf::Vector2f(endPoint.x - startPoint.x, endPoint.y - startPoint.y)),
	m_start(startPoint),
	m_end(endPoint)

{
	// make
	const int n = std::floor(v2fDist(m_start, m_end) / std::abs(m_speed));
	for (int i = 0; i < n; i++)
	{
		advance();
	}
	//m_lines.push_back(sf::Vertex(m_end, m_teamColor)); // helps visualize errors
	m_startFixed = false;
}

void Ray::advance()
{
	if (!m_endFixed)
	{
		float nextY = m_amp * static_cast<float>(cosf(m_freq * m_tPar + m_phase)); // todo: reduce sin calls

		float r = v2fDist(sf::Vector2f(0.f, 0.f), m_dir);
		float xRot = m_tPar * m_dir.x / r - nextY * m_dir.y / r;
		float yRot = m_tPar * m_dir.y / r + nextY * m_dir.x / r;

		float x = xRot + m_origin.x;
		float y = yRot + m_origin.y;

		m_lines.push_back(sf::Vertex(sf::Vector2f(x, y), m_teamColor));

		m_tPar += m_speed;
	}
	if (!m_startFixed)
	{
		m_lines.erase(m_lines.begin());
	}
}

void Ray::update()
{
	advance();
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// update vertex array of lines to display ray
	target.draw(m_lines.data(), m_lines.size(), sf::LinesStrip, states);
}
}