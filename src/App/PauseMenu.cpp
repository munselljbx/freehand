#include "PauseMenu.hpp"

namespace app
{

PauseMenu::PauseMenu(const sf::Texture& backgroundTex)
{
	m_background.setTexture(backgroundTex);
}

void PauseMenu::run(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("content/fonts/Ubuntu-Title.ttf");
	sf::Text text("paused", font, 50U);
	sf::Vector2f windowSize = window.mapPixelToCoords(static_cast<sf::Vector2i>(window.getSize()));
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	while (window.isOpen() && !m_exit)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				m_exit = true;
			}
		}

		window.clear();
		window.draw(m_background);
		window.draw(text);
		window.display();
	}
}
}