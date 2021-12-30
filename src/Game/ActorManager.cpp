#include "ActorManager.hpp"

namespace game
{
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
}

}