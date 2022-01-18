#include "ActorManager.hpp"

namespace game
{
void ActorManager::update(float chalk)
{
	// collision todo
	for (auto& ray : m_rayPool.m_data)
	{
		if (ray.inUse)
		{
			for (auto& b : m_boundaryPool.m_data)
			{
				if (b.inUse)
				{
					ray.collide(b);
				}
			}
		}
	}

	// update rays
	for (auto& i : m_rayPool.m_data)
	{
		if (i.inUse)
		{
			i.update(*m_map);
		}
	}

	for (auto& i : m_sources)
	{
		i.update(chalk);
	}
}

void ActorManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : m_rayPool.m_data)
	{
		if (i.inUse)
			target.draw(i, states);
	}
	for (auto& i : m_boundaryPool.m_data)
	{
		if (i.inUse)
			target.draw(i, states);
	}
	for (auto& i : m_sources)
	{
		target.draw(i, states);
	}
}
}