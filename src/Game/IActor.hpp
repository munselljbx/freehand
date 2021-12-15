#ifndef GAME_IACTOR_HPP
#define GAME_IACTOR_HPP

#include <SFML/Graphics.hpp>

namespace game
{
class IActor : public sf::Drawable
{ // Interface for objects which have physics updates are are drawn to the window
public:
	virtual ~IActor() = default;
	virtual void update() = 0;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
}

#endif // GAME_IACTOR_HPP