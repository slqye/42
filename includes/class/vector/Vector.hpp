#pragma once

#include <vector>
#include <stdexcept>
#include "class/matrix/Matrix.hpp"
#include "class/fn/Fn.hpp"

template <typename K>
class Matrix;

template <typename K>
class Vector
{
	public:
		Vector(const std::vector<K> &);
		Vector(const unsigned int &, const K &);
		~Vector();

		K &operator[](const unsigned long &);
		const K &operator[](const unsigned long &) const;

		void add(const Vector<K> &);
		void sub(const Vector<K> &);
		void scl(const K &);
		Matrix<K> reshape(const unsigned int &, const unsigned int &);
		const std::pair<const unsigned int, const unsigned int> get_shape(void) const;

		// 03
		K dot(const Vector<K> &) const;

		// 04
		float norm_1(void) const;
		float norm(void) const;
		float norm_inf(void) const;

	private:
		std::vector<K> _value;
};

template <typename K>
std::ostream & operator << (std::ostream &, const Vector<K> &);