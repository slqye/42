#include "class/fn/Fn.hpp"

// 14
template <typename K>
Matrix<K> Fn<K>::projection(const float &fov, const float &ratio, const float &near, const float &far)
{
	Matrix<K>	result(4 * 4, 0, 4, 4);
	float theta = fov / 2;
	float right = std::tan(theta) * near; // TOA: tan(theta) = oposite / adjacent | oposite = than(theta) * adjacent
	float left = -right;
	float top = (2 * right) / ratio / 2; // w / h = ratio | w = ratio * h | w / ratio = h
	float bottom = -top;

	result[{0, 0}] = 2 * near / (right - left);
	result[{1, 1}] = 2 * near / (top - bottom);
	result[{2, 2}] = -(far + near) / (far - near);
	result[{2, 3}] = K(-1);
	result[{0, 2}] = (right + left) / (right - left);
	result[{1, 3}] = (top + bottom) / (top - bottom);
	result[{3, 2}] = -(2 * far * near) / (far - near);
	return (result);
}
