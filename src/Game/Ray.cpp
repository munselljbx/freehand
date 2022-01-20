#include "Ray.hpp"

namespace game
{
Ray::Ray() :
	IActor(sf::Uint8(0U), 0.f, m_MAX_HEALTH)
{
}

void Ray::setFields(sf::Uint8 team, float health, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float frequency, float amplitude, float speed, float phase, bool reflecting)
{
	IActor::init(team, health, m_MAX_HEALTH);
	updateAlpha();
	m_points.clear();
	startFixed = true;
	endFixed = false;
	collisionFrame = false;
	m_tPar = -speed;
	m_freq = frequency;
	m_amp = amplitude;
	m_speed = speed;
	m_phase = phase;
	m_origin = sf::Vector2f(startPoint.x, startPoint.y);
	m_dir = endPoint - startPoint;
	m_start = startPoint;
	m_end = startPoint;
	m_healthPerLength = health / v2fDist(sf::Vector2f(0.f, 0.f), endPoint - startPoint);

	const int n = std::floor(v2fDist(startPoint, endPoint) / std::abs(m_speed));
	if (!reflecting)
	{
		m_freezeStartSteps = 0U;
		// make
		for (int i = 0; i < n; i++)
		{
			advance();
		}
		//m_points.push_back(sf::Vertex(m_end, m_color)); // helps visualize errors
		startFixed = false;
		setHealth(health);
	}
	else
	{
		// todo: fix health; health decreases bit by bit with this method
		m_health = 0.f;
		m_freezeStartSteps = n;
	}
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
		if (inArea)
		{ // exit?
			inArea = map.inArea(m_team, m_start);
		}
		else
		{ // enter?
			inArea = map.inArea(m_team, m_end);
		}

		if (!collisionFrame)
		{
			endFixed = false;
		}

		// move one frame
		advance();
		collisionFrame = false;
	}
}

void Ray::advance()
{
	float r = v2fDist(sf::Vector2f(0.f, 0.f), m_dir);
	if (!endFixed)
	{
		m_tPar += m_speed;
		float nextY = m_amp * static_cast<float>(cosf(m_freq * m_tPar + m_phase)); // todo: reduce sin calls

		float xRot = m_tPar * m_dir.x / r - nextY * m_dir.y / r;
		float yRot = m_tPar * m_dir.y / r + nextY * m_dir.x / r;

		float x = xRot + m_origin.x;
		float y = yRot + m_origin.y;

		m_points.push_back(sf::Vector2f(x, y));
		m_end += sf::Vector2f(m_speed * m_dir.x / r, m_speed * m_dir.y / r);
	}
	if (!startFixed)
	{

		if (m_points.size() > 2U)
		{
			m_points.erase(m_points.begin());
			m_start += sf::Vector2f(m_speed * m_dir.x / r, m_speed * m_dir.y / r);
		}
		else
		{
			setHealth(0.f);
			inUse = false;
		}
	}
	if (!startFixed && endFixed)
	{
		setHealth(m_health - m_healthPerLength * m_speed);
	}
	else if (startFixed && !endFixed)
	{
		setHealth(m_health + m_healthPerLength * m_speed);
	}

	if (m_freezeStartSteps > 0U)
	{
		if (m_freezeStartSteps == 1U)
		{
			startFixed = false;
		}
		m_freezeStartSteps--;
	}
}

void Ray::setHealth(float health)
{
	m_health = health;
	if (health <= 0.f)
		inUse = false;
}

float Ray::getHealthPerLength() const
{
	return m_healthPerLength;
}
float Ray::getTPar() const
{
	return m_tPar;
}
float Ray::getFrequency() const
{
	return m_freq;
}
float Ray::getAmplitude() const
{
	return m_amp;
}
float Ray::getSpeed() const
{
	return m_speed;
}
float Ray::getPhase() const
{
	return m_phase;
}
sf::Vector2f Ray::getDirection() const
{
	return m_dir;
}
sf::Vector2f Ray::getStart() const
{
	return m_start;
}
sf::Vector2f Ray::getEnd() const
{
	return m_end;
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