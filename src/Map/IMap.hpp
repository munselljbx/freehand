#ifndef MAP_IMAP_HPP
#define MAP_IMAP_HPP

#include "./Game/Source.hpp"

namespace map
{
class Source;
class IMap : public sf::Drawable
{
public:
	virtual bool inArea(sf::Uint8 team, const sf::Vector2f& point) const = 0;
	virtual std::vector<game::Source> makeSources() const = 0;

protected:
	IMap(sf::Uint8 nTeams, sf::RenderWindow& window) :
		m_nTeams(nTeams),
		m_window(&window)
	{}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	const sf::Uint8 m_nTeams;

	sf::RenderWindow* m_window;
};
}

#endif // MAP_IMAP_HPP