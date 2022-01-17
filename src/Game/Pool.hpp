#ifndef GAME_POOL_HPP
#define GAME_POOL_HPP

#include "ActorManager.hpp"
#include "IActor.hpp"

namespace game
{
template <class T>
class Pool
{
public:
	Pool(size_t initSize) :
		m_data(initSize)
	{
		// Compile-time sanity check
		static_assert(std::is_base_of<IActor, T>::value, "Derived not derived from BaseClass");

		assert(initSize == m_data.size());
		//printf("Pool with size: %zu, %zu \n", initSize, m_data.size());
	}

	T& firstAvailable()
	{
		for (T& i : m_data)
		{
			if (!i.inUse)
			{
				return i;
			}
		}
		return m_data.emplace_back();
	}

	void add(T& toAdd)
	{
		toAdd.inUse = true;
		T& f = firstAvailable();
		f = toAdd;
	}

private:
	std::vector<T> m_data;

	friend class ActorManager;
};
}

#endif // GAME_POOL_HPP