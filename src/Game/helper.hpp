#ifndef GAME_HELPER_HPP
#define GAME_HELPER_HPP

namespace game
{
inline float v2fDist(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return std::sqrt(dx * dx + dy * dy);
}
} // namespace game

#endif // GAME_HELPER_HPP