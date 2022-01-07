#ifndef SETTINGS_GAMESETTINGS_HPP
#define SETTINGS_GAMESETTINGS_HPP

namespace settings
{
struct GameSettings
{
public:
	inline static const float WORLD_X_MAX = 1600.f;
	inline static const float WORLD_Y_MAX = 900.f;

	inline static sf::Vector2f windowSize = sf::Vector2f(0.f, 0.f);

	inline static sf::Vector2f worldToCoord(const sf::Vector2f& worldPos)
	{ // coord is sfml coords -- top left origin and top right of window is window size
		// world is bottom left origin and top right of window is (WORLD_X_MAX, WORLD_Y_MAX)
		sf::Vector2f coordPos;
		coordPos.x = worldPos.x * (windowSize.x / WORLD_X_MAX);
		coordPos.y = -worldPos.y * (windowSize.y / WORLD_Y_MAX) + windowSize.y;
		return coordPos;
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
};
}

#endif // SETTINGS_GAMESETTINGS_HPP