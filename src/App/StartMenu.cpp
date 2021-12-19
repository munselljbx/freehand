#include "StartMenu.hpp"

namespace app
{
void StartMenu::run(sf::RenderWindow& window)
{
	while (window.isOpen() && !m_exit)
	{
		window.clear();
		window.display();

		m_exit = true;
	}
}
}