#include "class/fn/Fn.hpp"

template <typename K>
K Fn<K>::abs(const K &value)
{
	return (value < 0 ? value * -1.0f : value);
}

template <typename K>
K Fn<K>::pow(const K &value, const float &p)
{
	return (std::pow(value, p));
}