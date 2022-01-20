#ifndef GAME_ACTORMANAGER_HPP
#define GAME_ACTORMANAGER_HPP

#include "./Map/Imap.hpp"
#include "Boundary.hpp"
#include "Pool.hpp"
#include "Ray.hpp"
#include "Source.hpp"

namespace game
{
class ActorManager : public sf::Drawable
{
public:
	ActorManager(map::IMap& map) :
		m_sources(map.makeSources()),
		m_boundaryPool(20U),
		m_rayPool(30U),
		m_map(&map)
	{
	}
	void update(float chalk);
	void collide(Ray& ray, Boundary& bound);
	void collide(Ray& ray, Source& source);

	std::vector<Source> m_sources;
	Pool<Boundary> m_boundaryPool;
	Pool<Ray> m_rayPool;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	map::IMap* m_map;

	inline const static float m_MIN_SPLIT_LENGTH = 20.f;
};
} // namespace game

#endif //GAME_ACTORMANAGER_HPP