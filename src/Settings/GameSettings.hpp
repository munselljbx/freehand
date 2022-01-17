#ifndef SETTINGS_GAMESETTINGS_HPP
#define SETTINGS_GAMESETTINGS_HPP

namespace settings
{
struct GameSettings
{
public:
	// Manual set
	inline static const float WORLD_X_MAX = 1600.f;
	inline static const float WORLD_Y_MAX = 900.f;

	inline static const float MAX_CHALK = 1000.f;
	inline static const float CHALK_PER_TICK = 0.5;

	inline static const float DIST_PER_SIDE_CIRCLE = 3.f;

	inline static unsigned int circleNSides(float radius)
	{
		return static_cast<unsigned int>(radius * 2.f * ((float)M_PI / DIST_PER_SIDE_CIRCLE));
	}

	inline static sf::Color getTeamColor(sf::Uint8 team)
	{
		switch (team)
		{
			case sf::Uint8(1U):
				return sf::Color::White;
				break;
			case sf::Uint8(2U):
				return sf::Color::Yellow;
				break;
			default:
				return sf::Color::White;
				break;
		}
	}
	// Set on setup
	inline static sf::Vector2f windowSize = sf::Vector2f(0.f, 0.f);

	// Helper fns
	inline static bool inWorld(const sf::Vector2f& worldPos)
	{
		return worldPos.x >= 0.f && worldPos.y >= 0.f && worldPos.x <= WORLD_X_MAX && worldPos.y <= WORLD_Y_MAX;
	}

	inline static sf::Vector2f worldToCoord(const sf::Vector2f& worldPos)
	{ // coord is sfml coords -- top left origin and top right of window is window size
		// world is bottom left origin and top right of window is (WORLD_X_MAX, WORLD_Y_MAX)
		sf::Vector2f coordPos;
		coordPos.x = worldPos.x * (windowSize.x / WORLD_X_MAX);
		coordPos.y = -worldPos.y * (windowSize.y / WORLD_Y_MAX) + windowSize.y;
		return coordPos;
	}

	inline static sf::Vector2f coordToWorld(const sf::Vector2f& coordPos)
	{ // coord is sfml coords -- top left origin and top right of window is window size
		// world is bottom left origin and top right of window is (WORLD_X_MAX, WORLD_Y_MAX)
		sf::Vector2f worldPos;
		worldPos.x = coordPos.x * (WORLD_X_MAX / windowSize.x);
		worldPos.y = (windowSize.y - coordPos.y) * (WORLD_Y_MAX / windowSize.y);
		return worldPos;
	}
};
}

#endif // SETTINGS_GAMESETTINGS_HPP