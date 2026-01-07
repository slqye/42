#include "class/fn/Fn.hpp"

template <typename K>
float Fn<K>::angle_cos(const Vector<K> &u, const Vector<K> &v)
{
	std::pair<const unsigned int, const unsigned int> shape = v.get_shape();

	if (u.get_shape().first != shape.first)
		throw (std::logic_error("Vectors dimensions are different."));
	return ((u.dot(v)) / (u.norm() * v.norm()));
}