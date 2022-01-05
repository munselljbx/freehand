#ifndef GAME_ACTORMANAGER_HPP
#define GAME_ACTORMANAGER_HPP

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
		m_boundaryPool(10U),
		m_rayPool(30U)
	{}
	void update();

	//Pool<Source> m_sourcePool;
	Pool<Boundary> m_boundaryPool;
	Pool<Ray> m_rayPool;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
} // namespace game

#endif //GAME_ACTORMANAGER_HPP