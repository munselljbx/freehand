#ifndef APP_IAPPMENU_HPP
#define APP_IAPPMENU_HPP

namespace app
{
class IAppMenu
{
public:
	virtual ~IAppMenu() = default;
	virtual void run(sf::RenderWindow& window) = 0;

protected:
	const static int MENU_FPS = 60;
	bool m_exit = false;
};
} // namespace app

#endif // APP_IAPPMENU_HPP