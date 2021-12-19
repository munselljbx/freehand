#ifndef APP_PAUSEMENU_HPP
#define APP_PAUSEMENU_HPP

#include "App.hpp"
#include "IAppMenu.hpp"

namespace app
{
class PauseMenu : public IAppMenu
{
public:
	PauseMenu(const sf::Texture& backgroundTex) :
		IAppMenu(backgroundTex)
	{}
	void run(sf::RenderWindow& window);
};
} // namespace app

#endif // APP_PAUSEMENU_HPP