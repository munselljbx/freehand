#include "IAppMenu.hpp"

namespace app
{
IAppMenu::IAppMenu() {
}
IAppMenu::IAppMenu(const sf::Texture& backgroundTex) {
	m_background.setTexture(backgroundTex);
}
} // namespace app