#include "Ray.hpp"

namespace game
{
Ray::Ray() :
	IActor(sf::Uint8(0U), 0.f, m_MAX_HEALTH)
{
}

void Ray::setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase)
{
	IActor::init(team, health, m_MAX_HEALTH);
	m_points.clear();
	m_startFixed = true;
	m_endFixed = false;
	m_tPar = 0.f;
	m_freq = frequency;
	m_amp = amplitude;
	m_speed = speed;
	m_phase = phase;
	m_origin = sf::Vector2f(startPoint.x, startPoint.y);
	m_dir = sf::Vector2f(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
	m_start = startPoint;
	m_end = startPoint;

	// make
	const int n = std::floor(v2fDist(startPoint, endPoint) / std::abs(m_speed));
	for (int i = 0; i < n; i++)
	{
		advance();
	}
	//m_points.push_back(sf::Vertex(m_end, m_color)); // helps visualize errors
	m_startFixed = false;
}

void Ray::update(const map::IMap& map)
{
	if (!settings::GameSettings::inWorld(m_start))
	{ // still in bounds?
		inUse = false;
	}
	else
	{
		// inArea?
		inArea = map.inArea(m_team, m_end);
		// move one frame
		advance();
	}
}

void Ray::advance()
{
	float r = v2fDist(sf::Vector2f(0.f, 0.f), m_dir);
	if (!m_endFixed)
	{
		float nextY = m_amp * static_cast<float>(cosf(m_freq * m_tPar + m_phase)); // todo: reduce sin calls

		float xRot = m_tPar * m_dir.x / r - nextY * m_dir.y / r;
		float yRot = m_tPar * m_dir.y / r + nextY * m_dir.x / r;

		float x = xRot + m_origin.x;
		float y = yRot + m_origin.y;

		m_points.push_back(sf::Vector2f(x, y));
		m_end += sf::Vector2f(m_speed * m_dir.x / r, m_speed * m_dir.y / r);

		m_tPar += m_speed;
	}
	if (!m_startFixed)
	{
		m_start += sf::Vector2f(m_speed * m_dir.x / r, m_speed * m_dir.y / r);
		m_points.erase(m_points.begin());
	}
}

void Ray::collide(Boundary& bound)
{
	sf::Vector2f intersect(0.f, 0.f);
	bool doesCollide = getLineIntersection(bound.getStart(), bound.getEnd(), m_start, m_end, intersect);
	if (doesCollide)
	{
		float h = bound.getHealth();
		bound.setHealth(h - m_health);
		setHealth(m_health - h);
	}
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// update vertex array of lines to display ray
	sf::VertexArray sinGraphic(sf::LineStrip, m_points.size());
	for (size_t i = 0U; i < m_points.size(); i++)
	{
		sinGraphic[i] = sf::Vertex(settings::GameSettings::worldToCoord(m_points[i]), m_color);
	}
	target.draw(sinGraphic, states);

	sf::VertexArray midlineGraphic(sf::LineStrip, 2);
	midlineGraphic[0] = sf::Vertex(settings::GameSettings::worldToCoord(m_start), m_color);
	midlineGraphic[1] = sf::Vertex(settings::GameSettings::worldToCoord(m_end), m_color);
	target.draw(midlineGraphic, states);
}
}