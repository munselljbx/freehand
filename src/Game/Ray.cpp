#include "Ray.hpp"

namespace game
{
Ray::Ray() :
	IActor(sf::Uint8(0U), 0.f, m_MAX_HEALTH)
{
}
Ray::Ray(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase) :
	IActor(team, health, m_MAX_HEALTH),
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
	//m_points.push_back(sf::Vertex(m_end, m_teamColor)); // helps visualize errors
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

		m_points.push_back(sf::Vector2f(x, y));

		m_tPar += m_speed;
	}
	if (!m_startFixed)
	{
		m_points.erase(m_points.begin());
	}
}

void Ray::update()
{
	advance();
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// update vertex array of lines to display ray
	sf::VertexArray graphic(sf::LineStrip, m_points.size());
	for (size_t i = 0U; i < m_points.size(); i++)
	{
		graphic[i] = sf::Vertex(settings::GameSettings::worldToCoord(m_points[i]), m_teamColor);
	}
	target.draw(graphic, states);
}
}