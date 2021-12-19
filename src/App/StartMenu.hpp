#ifndef APP_STARTMENU_HPP
#define APP_STARTMENU_HPP

#include "IAppMenu.hpp"

namespace app
{
class StartMenu : public IAppMenu
{
public:
	virtual void run(sf::RenderWindow& window);
};
}

#endif // APP_STARTMENU_HPP