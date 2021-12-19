#ifndef GAME_PLAYAREA_HPP
#define GAME_PLAYAREA_HPP

namespace game
{
class PlayArea : sf::Drawable
{
public:
	bool inBounds(const sf::Vector2f& pos);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
} // namespace game

#endif