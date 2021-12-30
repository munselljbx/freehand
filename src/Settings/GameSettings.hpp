#ifndef SETTINGS_GAMESETTINGS_HPP
#define SETTINGS_GAMESETTINGS_HPP

namespace settings
{
struct GameSettings
{
public:
	static sf::Color getTeamColor(sf::Uint8 team)
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