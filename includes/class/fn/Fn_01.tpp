#include "class/fn/Fn.hpp"

template <typename K>
Vector<K> Fn<K>::linear_combination(const std::vector<Vector<K>> &vectors, const std::vector<K> &scalars)
{
	Vector<K> result(vectors[0].get_shape().first, 0);
	std::vector<Vector<K>> vectors_copy(vectors.begin(), vectors.end());
	std::vector<K> scalars_copy(scalars.begin(), scalars.end());

	if (vectors.size() != scalars.size())
		throw (std::logic_error("Arrays sizes are differents."));
	for (unsigned long i = 0; i < scalars.size(); i++)
	{
		vectors_copy[i].scl(scalars_copy[i]);
		result.add(vectors_copy[i]);
	}
	return (result);
}