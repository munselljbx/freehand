#include "DrawControl.hpp"

namespace game
{
void DrawControl::startDraw()
{
	if (!m_isDrawing)
	{
		std::cout << "draw" << std::endl;
		m_isDrawing = true;
	}
}

void DrawControl::stopDraw()
{
	if (m_isDrawing)
	{
		std::cout << "stop draw" << std::endl;
		if (m_points.size() > m_MIN_POINTS && !evaluateLine())
		{
			//evaluateSine();
		}
		m_points.clear();
		m_isDrawing = false;
	}
}

void DrawControl::addPoint(const sf::Vector2f& pos)
{
	if (m_isDrawing)
	{
		m_points.push_back(pos);
	}
}

void DrawControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isDrawing)
	{
		for (auto i : m_points)
		{
			m_dot.setPosition(i);
			target.draw(m_dot, states);
		}
	}
}

bool DrawControl::evaluateLine()
{
	const size_t count = m_points.size();
	if (count == 0)
	{
		return false;
	}

	// means
	float sumX = 0.f;
	float sumY = 0.f;
	for (const auto& i : m_points)
	{
		sumX += i.x;
		sumY += i.y;
	}
	const float meanX = sumX / count;
	const float meanY = sumY / count;

	//slope
	float numerator = 0.0f;
	float denominator = 0.0f;
	float xOff;

	for (const auto& i : m_points)
	{
		xOff = i.x - meanX;
		numerator += xOff * (i.y - meanY);
		denominator += xOff * xOff;
	}

	const float m = numerator / denominator; // y=mx+b
	const float b = meanY - m * meanX;

	// err
	const float c1 = denominator; // c1*x+c2*y+c3=0
	const float c2 = -numerator;
	const float c3 = -b * denominator;
	float err = 0;
	//const float OUTLIER_CUT = 100.f;
	int n_outliers = 0;
	for (const auto& i : m_points)
	{
		float t = (c1 * i.x + c2 * i.y + c3);
		float perpDist = (t * t) / (c1 * c1 + c2 * c2); // perp dist to line squared
		err += perpDist;
		//if (perpDist > OUTLIER_CUT)
		//n_outliers++;
	}
	const float meanErr = err / count;
	if (n_outliers > 1)
		return false;

	// endpoints
	sf::Vector2f first = m_points.front();
	first.y -= b;
	const float sCoef = (first.x * denominator + first.y * numerator) / (numerator * numerator + denominator * denominator);
	sf::Vector2f startPoint = sf::Vector2f(sCoef * denominator, sCoef * numerator + b);

	sf::Vector2f last = m_points.back();
	last.y -= b;
	const float eCoef = (last.x * denominator + last.y * numerator) / (numerator * numerator + denominator * denominator);
	sf::Vector2f endPoint = sf::Vector2f(eCoef * denominator, eCoef * numerator + b);

	// health
	float health = 0;
	float length = v2fDist(startPoint, endPoint);
	if (meanErr > 0.f)
	{
		health = 1 / meanErr * length;
	}
	else
	{
		health = length;
	}

	// make Boundary
	std::cout << "Start make bound" << std::endl;
	Boundary bound(sf::Uint8(1U), health, startPoint, endPoint);
	m_actors->m_boundaryPool.add(bound);
	std::cout << "Done make bound" << std::endl;
	return true;
}

bool DrawControl::evaluateSine()
{
	// make Forbiddence
	return true;
}

}