#include "class/fn/Fn.hpp"

template <typename K>
K Fn<K>::lerp(const K &u, const K &v, const float &t)
{
	if (t < 0 || t > 1)
		throw (std::logic_error("Lerping is only allowed for t ∈ [0; 1]."));
	return (u + ((v - u) * t));
}

template <typename K>
Vector<K> Fn<K>::lerp(const Vector<K> &u, const Vector<K> &v, const float &t)
{
	std::pair<const unsigned int, const unsigned int> shape = u.get_shape();
	Vector<K> result(shape.first, 0);

	if (shape.first != v.get_shape().first)
		throw (std::logic_error("Vectors dimensions are different."));
	if (t < 0 || t > 1)
		throw (std::logic_error("Lerping is only allowed for t ∈ [0; 1]."));
	for (unsigned int i = 0; i < shape.first; i++)
		result[i] = Fn<K>::lerp(u[i], v[i], t);
	return (result);
}

template <typename K>
Matrix<K> Fn<K>::lerp(const Matrix<K> &u, const Matrix<K> &v, const float &t)
{
	std::pair<const unsigned int, const unsigned int> shape = u.get_shape();
	Matrix<K> result(shape.first * shape.second, 0, shape.first, shape.second);

	if (shape.first != v.get_shape().first && shape.second != v.get_shape().second)
		throw (std::logic_error("Vectors dimensions are different."));
	if (t < 0 || t > 1)
		throw (std::logic_error("Lerping is only allowed for t ∈ [0; 1]."));
	for (unsigned int i = 0; i < shape.first; i++)
	{
		for (unsigned int j = 0; j < shape.second; j++)
			result[{i, j}] = Fn<K>::lerp(u[{i, j}], v[{i, j}], t);
	}
	return (result);
}