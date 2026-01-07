#include "class/complex/Complex.hpp"

Complex::Complex(void)
{
	this->_a = 0;
	this->_b = 0;
}

Complex::Complex(const float &a, const float &b)
{
	this->_a = a;
	this->_b = b;
}

Complex::Complex(const float &a)
{
	this->_a = a;
	this->_b = 0;
}

Complex::~Complex()
{
}

std::pair<float, float> Complex::get_value(void) const
{
	return (std::make_pair(this->_a, this->_b));
}

std::ostream &operator<<(std::ostream &stream, const Complex &complex)
{
	if (complex.get_value().first == 0 && complex.get_value().second == 0)
		stream << "0";
	else if (complex.get_value().first == 0)
		stream << "0" << " + i * " << complex.get_value().second;
	else if (complex.get_value().second == 0)
		stream << complex.get_value().first;
	else
		stream << complex.get_value().first << " + i * " << complex.get_value().second;
	return (stream);
}