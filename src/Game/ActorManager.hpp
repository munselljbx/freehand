#ifndef GAME_ACTORMANAGER_HPP
#define GAME_ACTORMANAGER_HPP

#include "./Map/Imap.hpp"
#include "Boundary.hpp"
#include "Pool.hpp"
#include "Ray.hpp"

namespace game
{
class ActorManager : public sf::Drawable
{
public:
	ActorManager() :
		//m_sourcePool(m_INITIAL_SOURCE_SIZE),
		m_boundaryPool(20U),
		m_rayPool(30U)
	{}
	void update(const map::IMap& map);

	//Pool<Source> m_sourcePool;
	Pool<Boundary> m_boundaryPool;
	Pool<Ray> m_rayPool;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
} // namespace game

#endif //GAME_ACTORMANAGER_HPP