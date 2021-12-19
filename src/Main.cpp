#include "App/App.hpp"
#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "DEBUG!" << std::endl;
#endif

	sf::RenderWindow window;
	app::App theApp = app::App(window);
	theApp.run();

	std::cout << "EXIT: GOOD" << std::endl;
	return 0;
}
