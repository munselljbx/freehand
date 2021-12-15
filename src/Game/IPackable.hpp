#ifndef GAME_IPACKABLE_HPP
#define GAME_IPACKABLE_HPP

namespace game
{
class IPackable
{ // Object can produce a packet from its data for multiplayer
public:
	virtual ~IPackable() = default;

protected:
	virtual void pack(sf::Packet& packet) const = 0;
};
}

#endif // GAME_IPACKABLE_HPP