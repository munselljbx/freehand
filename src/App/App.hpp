#ifndef APP_APP_HPP
#define APP_APP_HPP

#include "./Game/World.hpp"
#include "./Map/Duel.hpp"
#include "./Map/IMap.hpp"
#include "./Platform/Platform.hpp"
#include "StartMenu.hpp"

namespace app
{
class App
{
public:
	App(sf::RenderWindow& window);
	~App()
	{
		delete m_window;
	}
	void run();
	void applyCursor();
	sf::RenderWindow& getWindow() const;

private:
	sf::RenderWindow* m_window;
	sf::WindowHandle m_systemHandle;
	util::Platform m_platform;
	sf::Cursor m_cursor;
};
} // namespace app

#endif // APP_APP_HPP