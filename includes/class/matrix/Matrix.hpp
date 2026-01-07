#pragma once

#include <vector>
#include <stdexcept>
#include "class/vector/Vector.hpp"

template <typename K>
class Vector;

template <typename K>
class Matrix
{
	public:
		Matrix(const std::vector<K> &, const unsigned int &, const unsigned int &);
		Matrix(const unsigned int &, const K &, const unsigned int &, const unsigned int &);
		~Matrix();

		Matrix<K> &operator=(const Matrix<K> &);
		K &operator[](const std::pair<const unsigned int, const unsigned int> &);
		const K &operator[](const std::pair<const unsigned int, const unsigned int> &) const;

		bool is_null(void) const;

		void add(const Matrix<K> &);
		void sub(const Matrix<K> &);
		void scl(const K &);
		Vector<K> reshape(void);
		const std::pair<const unsigned int, const unsigned int> get_shape(void) const;

		// 07
		Vector<K> mul_vec(const Vector<K> &);
		Matrix<K> mul_mat(const Matrix<K> &);

		// 08
		K trace(void) const;

		// 09
		Matrix<K> transpose(void);

		// 10
		static unsigned int col_max_index(const Matrix<K> &, const unsigned int &, const unsigned int &);
		void swap_row(const unsigned int &, const unsigned int &);
		Matrix<K> row_echelon(void);

		// 11
		K determinant(void);

		// 12
		Matrix<K> inverse(void);

		// 13
		unsigned int rank(void);

	private:
		unsigned int _m;
		unsigned int _n;
		std::vector<K> _value;
};

template <typename K>
std::ostream & operator << (std::ostream &, const Matrix<K> &);