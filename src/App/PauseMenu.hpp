#ifndef APP_PAUSEMENU_HPP
#define APP_PAUSEMENU_HPP

#include "IAppMenu.hpp"

namespace app
{
class PauseMenu : public IAppMenu
{
public:
	PauseMenu(const sf::Texture& backgroundTex);
	void run(sf::RenderWindow& window) override;

private:
	sf::Sprite m_background;
};
} // namespace app

#endif // APP_PAUSEMENU_HPP