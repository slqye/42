#include "class/vector/Vector.hpp"

// 00
template <typename K>
Vector<K>::Vector(const std::vector<K> &value)
{
	this->_value = value;
}

// 00
template <typename K>
Vector<K>::Vector(const unsigned int &size, const K &value)
{
	this->_value = std::vector<K>(size, value);
}

// 00
template <typename K>
Vector<K>::~Vector() {}

// 00
template <typename K>
K &Vector<K>::operator[](const unsigned long &i)
{
	if (i >= this->_value.size())
		throw (std::logic_error("Index out of range."));
	return (this->_value.at(i));
}

// 00
template <typename K>
const K &Vector<K>::operator[](const unsigned long &i) const
{
	if (i >= this->_value.size())
		throw (std::logic_error("Index out of range."));
	return (this->_value.at(i));
}

// 00
template <typename K>
void Vector<K>::add(const Vector<K> &other)
{
	std::pair<const unsigned int, const unsigned int> shape = other.get_shape();

	if (this->_value.size() != shape.first)
		throw (std::logic_error("Vectors dimensions are different."));
	for (unsigned long i = 0; i < this->_value.size(); i++)
	{
		this->_value[i] += other[i];
	}
}

// 00
template <typename K>
void Vector<K>::sub(const Vector<K> &other)
{
	std::pair<const unsigned int, const unsigned int> shape = other.get_shape();

	if (this->_value.size() != shape.first)
		throw (std::logic_error("Vectors dimensions are different."));
	for (unsigned long i = 0; i < this->_value.size(); i++)
	{
		this->_value[i] -= other[i];
	}
}

// 00
template <typename K>
void Vector<K>::scl(const K &scalar)
{
	for (unsigned long i = 0; i < this->_value.size(); i++)
	{
		this->_value[i] *= scalar;
	}
}

// 00
template <typename K>
Matrix<K> Vector<K>::reshape(const unsigned int &m, const unsigned int &n)
{
	return (Matrix<K>(this->_value, m, n));
}

// 00
template <typename K>
const std::pair<const unsigned int, const unsigned int> Vector<K>::get_shape(void) const
{
	return (std::make_pair(this->_value.size(), 1));
}

// 03
template <typename K>
K Vector<K>::dot(const Vector<K> &other) const
{
	std::pair<const unsigned int, const unsigned int> shape = other.get_shape();
	K result = K();

	if (this->_value.size() != shape.first)
		throw (std::logic_error("Vectors dimensions are different."));
	for (unsigned int i = 0; i < this->_value.size(); i++)
		result += this->_value[i] * other[i];
	return (result);
}

// 04
template <typename K>
float Vector<K>::norm_1(void) const
{
	float result = K();

	for (unsigned int i = 0; i < this->_value.size(); i++)
		result += Fn<K>::abs(this->_value[i]);
	return (result);
}

// 04
template <typename K>
float Vector<K>::norm(void) const
{
	float result = K();

	for (unsigned int i = 0; i < this->_value.size(); i++)
		result += Fn<K>::pow(this->_value[i], 2); // todo abs for complex
	return (Fn<K>::pow(result, 0.5f));
}

template <typename K>
float Vector<K>::norm_inf(void) const
{
	float result = K();

	for (unsigned int i = 0; i < this->_value.size(); i++)
		Fn<K>::abs(this->_value[i]) > result ? result = Fn<K>::abs(this->_value[i]) : result;
	return (result);
}

// 00
template <typename K>
std::ostream &operator<<(std::ostream &stream, const Vector<K> &vector)
{
	std::pair<const unsigned int, const unsigned int> shape = vector.get_shape();

	for (unsigned long i = 0; i < shape.first; i++)
	{
		i != shape.first - 1 ? stream << "[" << vector[i] << "]\n" : stream << "[" << vector[i] << "]";
	}
	return (stream);
}