#include "Game/App.hpp"

int main()
{

#if defined(_DEBUG)
	std::cout << "DEBUG!" << std::endl;
#endif

	game::App freehand = game::App();
	freehand.run();

	return 0;
}
