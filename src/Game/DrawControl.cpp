#include "DrawControl.hpp"

namespace game
{
void DrawControl::startDraw()
{
	if (!m_isDrawing)
	{
		m_isDrawing = true;
	}
}
void DrawControl::stopDraw()
{
	if (m_isDrawing)
	{
		// evaluateDrawing()
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

}