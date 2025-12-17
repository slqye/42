#include "class/matrix/Matrix.hpp"

// 00
template <typename K>
Matrix<K>::Matrix(const std::vector<K> &value, const unsigned int &m, const unsigned int &n)
{
	if (m * n != value.size())
		throw (std::logic_error("Matrix size is incorrect."));
	this->_m = m;
	this->_n = n;
	this->_value = value;
}

// 00
template <typename K>
Matrix<K>::Matrix(const unsigned int &size, const K &value, const unsigned int &m, const unsigned int &n)
{
	if (m * n != size)
		throw (std::logic_error("Matrix size is incorrect."));
	this->_m = m;
	this->_n = n;
	this->_value = std::vector<K>(size, value);
}

// 00
template <typename K>
Matrix<K>::~Matrix() {}

// 10
template <typename K>
Matrix<K> &Matrix<K>::operator=(const Matrix<K> &other)
{
	if (this != &other)
	{
		this->_value = other._value;
		this->_m = other._m;
		this->_n = other._n;
	}
	return (*this);
}

// 00
template <typename K>
K &Matrix<K>::operator[](const std::pair<const unsigned int, const unsigned int> &pair)
{
	unsigned int index = this->_n * pair.first + pair.second;

	if (index >= this->_value.size())
		throw (std::logic_error("Index out of range."));
	return (this->_value.at(index));
}

// 00
template <typename K>
const K &Matrix<K>::operator[](const std::pair<const unsigned int, const unsigned int> &pair) const
{
	unsigned int index = this->_n * pair.first + pair.second;

	if (index >= this->_value.size())
		throw (std::logic_error("Index out of range."));
	return (this->_value.at(index));
}

// 00
template <typename K>
bool Matrix<K>::is_null(void) const
{
	if (this->_m == 0 && this->_n == 0)
		return (true);
	return (false);
}

// 00
template <typename K>
void Matrix<K>::add(const Matrix<K> &other)
{
	std::pair<const unsigned int, const unsigned int> shape = other.get_shape();

	if (this->_m != shape.first || this->_n != shape.second)
		throw (std::logic_error("Matrices dimensions are different."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			this->_value[this->_n * i + j] += other[{i, j}];
		}
	}
}

// 00
template <typename K>
void Matrix<K>::sub(const Matrix<K> &other)
{
	std::pair<const unsigned int, const unsigned int> shape = other.get_shape();

	if (this->_m != shape.first || this->_n != shape.second)
		throw (std::logic_error("Matrices dimensions are different."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			this->_value[this->_n * i + j] -= other[{i, j}];
		}
	}
}

// 00
template <typename K>
void Matrix<K>::scl(const K &scalar)
{
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			this->_value[this->_n * i + j] *= scalar;
		}
	}
}

// 00
template <typename K>
Vector<K> Matrix<K>::reshape(void)
{
	return (Vector<K>(this->_value));
}

// 00
template <typename K>
const std::pair<const unsigned int, const unsigned int> Matrix<K>::get_shape(void) const
{
	return (std::make_pair(this->_m, this->_n));
}

// 07
template <typename K>
Vector<K> Matrix<K>::mul_vec(const Vector<K> &other)
{
	Vector<K> result(this->_m, 0);

	if (this->_n != other.get_shape().first)
		throw (std::logic_error("Vector's dimension is not supported."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			result[i] += this->_value[this->_n * i + j] * other[j];
		}
	}
	return (result);
}

// 07
template <typename K>
Matrix<K> Matrix<K>::mul_mat(const Matrix<K> &other)
{
	Matrix<K> result(this->_m * other.get_shape().second, 0, this->_m, other.get_shape().second);

	if (this->_n != other.get_shape().first)
		throw (std::logic_error("Matrix's dimension is not supported."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < other.get_shape().second; j++)
		{
			for (unsigned int k = 0; k < this->_n; k++)
			{
				result[{i, j}] += this->_value[this->_n * i + k] * other[{k, j}];
			}
		}
	}
	return (result);
}

// 08
template <typename K>
K Matrix<K>::trace(void) const
{
	K result = K();

	if (this->_m != this->_n)
		throw (std::logic_error("Matrix is not square."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		result += this->_value[this->_n * i + i];
	}
	return (result);
}

// 09
template <typename K>
Matrix<K> Matrix<K>::transpose(void)
{
	Matrix<K> result(this->_m * this->_n, 0, this->_n, this->_m);

	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			result[{j, i}] = this->_value[this->_n * i + j];
		}
	}
	return (result);
}

// 10
template <typename K>
unsigned int Matrix<K>::col_max_index(const Matrix<K> &matrix, const unsigned int &m, const unsigned int &n)
{
	K value = Fn<K>::abs(matrix[{m, n}]);
	unsigned int index = m;
	unsigned int a_max_rows = matrix.get_shape().first;

	for (unsigned int i = m; i < a_max_rows; i++)
	{
		if (Fn<K>::abs(matrix[{i, n}]) > value)
		{
			value = Fn<K>::abs(matrix[{i, n}]);
			index = i;
		}
	}
	return (index);
}

// 10
template <typename K>
void Matrix<K>::swap_row(const unsigned int &a, const unsigned int &b)
{
	K holder[this->_n];

	for (unsigned int i = 0; i < this->_n; i++)
	{
		holder[i] = this->_value[this->_n * a + i];
		this->_value[this->_n * a + i] = this->_value[this->_n * b + i];
		this->_value[this->_n * b + i] = holder[i];
	}
}

// 10
template <typename K>
Matrix<K> Matrix<K>::row_echelon(void)
{
	Matrix<K> result = *this;
	unsigned int h = 0;
	unsigned int k = 0;
	unsigned int i_max = 0;
	K factor;
	K holder;

	while (h < this->_m && k < this->_n)
	{
		i_max = Matrix<K>::col_max_index(*this, h, k);
		if (result[{i_max, k}] == 0)
		{
			k++;
		}
		else
		{
			result.swap_row(h, i_max);
			for (unsigned int i = h + 1; i < this->_m; i++)
			{
				factor = result[{i, k}] / result[{h, k}];
				result[{i, k}] = K();
				for (unsigned int j = k + 1; j < this->_n; j++)
				{
					result[{i, j}] -= result[{h, j}] * factor;
				}
			}
			holder = result[{h, k}];
			for (unsigned int i = k; i < this->_n; i++)
			{
				result[{h, i}] *= K(1) / holder;
			}
			if (h != 0)
			{
				for (int i = h - 1; i >= 0; i--)
				{
					factor = result[{i, k}] / result[{h, k}];
					for (unsigned int j = k; j < this->_n; j++)
					{
						result[{i, j}] -= result[{h, j}] * factor;
					}
				}
			}
			h++;
			k++;
		}
	}
	return (result);
}

// 11
template <typename K>
K Matrix<K>::determinant(void)
{
	K result = 1;
	Matrix<K> m_holder = *this;
	unsigned int h = 0;
	unsigned int k = 0;
	int i_max = 0;
	int swap_count = 0;
	K factor;


	if (this->_m != this->_n)
		throw (std::logic_error("Matrix is not square."));
	while (h < this->_m && k < this->_n)
	{
		i_max = Matrix<K>::col_max_index(*this, h, k);
		if (m_holder[{i_max, k}] == 0)
		{
			k++;
		}
		else
		{
			m_holder.swap_row(h, i_max);
			swap_count++;
			for (unsigned int i = h + 1; i < this->_m; i++)
			{
				factor = m_holder[{i, k}] / m_holder[{h, k}];
				m_holder[{i, k}] = K();
				for (unsigned int j = k + 1; j < this->_n; j++)
				{
					m_holder[{i, j}] -= m_holder[{h, j}] * factor;
				}
			}
			h++;
			k++;
		}
	}
	for (unsigned int i = 0; i < this->_m; i++)
	{
		result *= m_holder[{i, i}];
	}
	swap_count % 2 == 0 ? result *= -1 : result *= 1;
	return (result);
}

// 12
template <typename K>
Matrix<K> Matrix<K>::inverse(void)
{
	Matrix<K> augmented(this->_m * this->_m * 2, 0, this->_m, 2 * this->_n);
	Matrix<K> result(this->_m * this->_n, 0, this->_m, this->_n);
	K determinant;

	if (this->_m != this->_n)
		throw (std::logic_error("Matrix is not square."));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			augmented[{i, j}] = this->_value[this->_n * i + j];
		}
	}
	for (unsigned int i = this->_m; i < this->_m * 2; i++)
	{
		augmented[{i - this->_m, i}] = K(1);
	}
	Matrix<K> augmented_row_echelon = augmented.row_echelon();
	determinant = this->determinant();
	if (determinant == 0)
		return (Matrix<K>(0, 0, 0, 0));
	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			result[{i, j}] = augmented_row_echelon[{i, this->_n + j}];
		}
	}
	return (result);
}

// 13
template <typename K>
unsigned int Matrix<K>::rank(void)
{
	Matrix<K> holder = this->row_echelon();
	unsigned int rank = 0;

	for (unsigned int i = 0; i < this->_m; i++)
	{
		for (unsigned int j = 0; j < this->_n; j++)
		{
			if (holder[{i, j}] != K())
			{
				rank++;
				break ;
			}
		}
	}
	return (rank);
}

// 00
template <typename K>
std::ostream &operator<<(std::ostream &stream, const Matrix<K> &matrix)
{
	std::pair<const unsigned int, const unsigned int> shape = matrix.get_shape();

	if (matrix.is_null())
	{
		stream << "NULL_MATRIX";
		return (stream);
	}
	for (unsigned int i = 0; i < shape.first; i++)
	{
		stream << "[";
		for (unsigned int j = 0; j < shape.second; j++)
		{
			j != shape.second - 1 ? stream << matrix[{i, j}] << " " : stream << matrix[{i, j}];
		}
		i != shape.first - 1 ? stream << "]\n" : stream << "]";
	}
	return (stream);
}