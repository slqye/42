#include "class/fn/Fn.hpp"

template <typename K>
Vector<K> Fn<K>::cross_product(const Vector<K> &u, const Vector<K> &v)
{
	Vector<K> result(3, 0);

	std::pair<const unsigned int, const unsigned int> shape = v.get_shape();

	if (u.get_shape().first != shape.first)
		throw (std::logic_error("Vectors dimensions are different."));
	else if (shape.first != 3)
		throw (std::logic_error("Vectors dimensions need to be 3."));
	result[0] = u[1] * v[2] - u[2] * v[1];
	result[1] = u[2] * v[0] - u[0] * v[2];
	result[2] = u[0] * v[1] - u[1] * v[0];
	return (result);
}