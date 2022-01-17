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
inline bool getLineIntersection(const sf::Vector2f& line1Point1, const sf::Vector2f& line1Point2, const sf::Vector2f& line2Point1, const sf::Vector2f& line2Point2, sf::Vector2f& intersectionPoint)
{
	// modified from https://stackoverflow.com/a/1968345
	// intersectionPoint holds intersection point if return true
	float p0_x = line1Point1.x;
	float p0_y = line1Point1.y;
	float p1_x = line1Point2.x;
	float p1_y = line1Point2.y;
	float p2_x = line2Point1.x;
	float p2_y = line2Point1.y;
	float p3_x = line2Point2.x;
	float p3_y = line2Point2.y;

	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;
	s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;
	s2_y = p3_y - p2_y;

	float s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		intersectionPoint.x = p0_x + (t * s1_x);
		intersectionPoint.y = p0_y + (t * s1_y);
		return true;
	}

	return false; // No collision
}
} // namespace game

#endif // GAME_HELPER_HPP