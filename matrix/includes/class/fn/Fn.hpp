#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>
#include "class/vector/Vector.hpp"
#include "class/matrix/Matrix.hpp"

template <typename K>
class Vector;

template <typename K>
class Matrix;

template <typename K>
class Fn
{
	public:
		// 01
		static Vector<K> linear_combination(const std::vector<Vector<K>> &, const std::vector<K> &);

		// 02
		static K lerp(const K &, const K &, const float &);
		static Vector<K> lerp(const Vector<K> &, const Vector<K> &, const float &);
		static Matrix<K> lerp(const Matrix<K> &, const Matrix<K> &, const float &);

		// 04
		static K abs(const K &);
		static K pow(const K &, const float &);

		// 05
		static float angle_cos(const Vector<K> &, const Vector<K> &);

		// 06
		static Vector<K> cross_product(const Vector<K> &, const Vector<K> &);

		// 14
		static Matrix<K> projection(const float &, const float &, const float &, const float &);
};