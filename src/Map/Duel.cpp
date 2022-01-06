#include "Duel.hpp"

namespace map
{
Duel::Duel(sf::RenderWindow& window) :
	IMap(sf::Uint8(2U), window),
	m_dividerSize(sf::Vector2f(0.02f, 1.f)),
	m_dividerColor(sf::Color(255U, 175U, 30U))
{
	if (!m_backgroundTex.loadFromFile("content/textures/background.png"))
		throw "Failed to load background texture.";
	else
		m_background.setTexture(m_backgroundTex);
}

bool Duel::inArea(sf::Uint8 team, const sf::Vector2f& point) const
{
	sf::Vector2f fWindowSize = m_window->mapPixelToCoords(static_cast<sf::Vector2i>(m_window->getSize()));
	if (point.x < 0 || point.y < 0 || point.x > fWindowSize.x || point.y > fWindowSize.y)
		return false;

	float divX = fWindowSize.x / 2.f;
	if (team == 1U)
	{
		return point.x < divX;
	}
	else if (team == 2U)
	{
		return point.x > divX;
	}
	return false;
}

void Duel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vector2f windowSize = target.mapPixelToCoords(static_cast<sf::Vector2i>(target.getSize()));
	float wx = windowSize.x;
	float wy = windowSize.y;

	// background
	float ScaleX = wx / m_backgroundTex.getSize().x;
	float ScaleY = wy / m_backgroundTex.getSize().y;
	m_background.setScale(ScaleX, ScaleY);
	target.draw(m_background, states);

	// divider
	sf::VertexArray div(sf::Quads, 4U);
	for (size_t i = 0U; i < div.getVertexCount(); i++)
	{
		div[i].color = m_dividerColor;
	}
	div[0].position = sf::Vector2f(wx / 2.f - wx * m_dividerSize.x / 2.f, 0.f);
	div[1].position = sf::Vector2f(wx / 2.f + wx * m_dividerSize.x / 2.f, 0.f);
	div[2].position = sf::Vector2f(wx / 2.f + wx * m_dividerSize.x / 2.f, wy);
	div[3].position = sf::Vector2f(wx / 2.f - wx * m_dividerSize.x / 2.f, wy);

	target.draw(div, states);
}
} // namespace map