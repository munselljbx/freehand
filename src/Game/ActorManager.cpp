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
					collide(ray, b);
				}
			}
			for (auto& s : m_sources)
			{
				collide(ray, s);
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

void ActorManager::collide(Ray& ray, Boundary& bound)
{
	sf::Vector2f intersect(0.f, 0.f);
	bool doesCollide = getLineIntersection(bound.getStart(), bound.getEnd(), ray.getStart(), ray.getEnd(), intersect);
	if (doesCollide)
	{
		ray.collisionFrame = true;
		if (v2fDist(intersect, ray.getEnd()) > m_MIN_SPLIT_LENGTH && v2fDist(intersect, ray.getEnd()) > m_MIN_SPLIT_LENGTH)
		{	// todo: split
			// newRay on opposite side of boundary

			// ray is striking boundary
		}
		else if (v2fDist(intersect, ray.getEnd()) < ray.getSpeed() * 3.f
			&& v2fDist(ray.getStart(), ray.getEnd()) > m_MIN_SPLIT_LENGTH)
		{ // striking (ray end hit boundary)
			//todo: ray.replaceEnd(ray.worldToT(intersect));
			if (bound.getTeam() == ray.getTeam())
			{ // reflection
				if (!ray.endFixed)
				{
					sf::Vector2f bDir = bound.getEnd() - bound.getStart();
					sf::Vector2f rDir = ray.getDirection();
					float projRBCoef = (rDir.x * bDir.x + rDir.y * bDir.y) / (bDir.x * bDir.x + bDir.y * bDir.y);
					sf::Vector2f reflectDir = rDir;
					reflectDir -= 2.f * projRBCoef * bDir;
					reflectDir *= -1.f;
					sf::Vector2f reflectEnd = intersect + reflectDir;

					float phase = ray.getFrequency() * ray.getTPar() + ray.getPhase() + (float)M_PI;
					float n = floor(phase / (2.f * (float)M_PI));
					phase -= n * (2.f * (float)M_PI);
					Ray& newRay = m_rayPool.firstAvailable();
					newRay.setFields(ray.getTeam(), ray.getHealth(), intersect, reflectEnd, ray.getFrequency(), ray.getAmplitude(), ray.getSpeed(), phase, true);

					ray.endFixed = true;
				}
			}
			else
			{ // hurt enemy
				if (!ray.endFixed)
				{
					float bH = bound.getHealth();
					float rH = ray.getHealthPerLength();
					bound.setHealth(bH - rH);
					ray.setHealth(0.f);

					ray.endFixed = true;
				}
			}
		}
	}
}

void ActorManager::collide(Ray& ray, Source& source)
{
	sf::Vector2f sPos = source.getPosWorld();
	sf::Vector2f rPos = ray.getEnd();
	float r = source.getRadiusWorld();

	bool doesCollide = std::pow(rPos.x - sPos.x, 2.f) + std::pow(rPos.y - sPos.y, 2.f) <= r * r;
	if (doesCollide)
	{
		ray.collisionFrame = true;
		if (source.getTeam() == ray.getTeam())
		{ // no teamkill
			ray.endFixed = true;
		}
		else
		{ // damage enemy
			float sH = source.getHealth();
			float rH = ray.getHealth();
			source.setHealth(sH - rH);
			ray.setHealth(0.f);
		}
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