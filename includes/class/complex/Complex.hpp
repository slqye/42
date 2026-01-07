#pragma once

#include <vector>
#include <stdexcept>
#include "class/vector/Vector.hpp"
#include "class/matrix/Matrix.hpp"

class Complex
{
	public:
		Complex(void);
		Complex(const float &, const float &);
		Complex(const float &);
		~Complex();

		Complex &operator+=(const Complex &complex)
		{
			this->_a += complex.get_value().first;
			this->_b += complex.get_value().second;
			return (*this);
		}
		Complex &operator-=(const Complex &complex)
		{
			this->_a -= complex.get_value().first;
			this->_b -= complex.get_value().second;
			return (*this);
		}
		Complex &operator*=(const Complex &complex)
		{
			this->_a = this->_a * complex.get_value().first - this->_b * complex.get_value().second;
			this->_b = this->_a * complex.get_value().second + this->_b * complex.get_value().first;
			return (*this);
		}
		Complex operator*(const Complex &complex)
		{
			float a = this->_a * complex.get_value().first - this->_b * complex.get_value().second;
			float b = this->_a * complex.get_value().second + this->_b * complex.get_value().first;
			return (Complex(a, b));
		}
		Complex operator*(const float &value)
		{
			float a = this->_a * value;
			float b = this->_a * value;
			return (Complex(a, b));
		}
		const Complex operator*(const float &value) const
		{
			float a = this->_a * value;
			float b = this->_a * value;
			return (Complex(a, b));
		}
		Complex operator/(const Complex &complex)
		{
			float denom = complex.get_value().first * complex.get_value().first - complex.get_value().second * complex.get_value().second;
			if (denom == 0)
				throw (std::logic_error("Complex divsion per 0."));
			float a = (this->_a * complex.get_value().first + this->_b * complex.get_value().second) / denom;
			float b = (this->_b * complex.get_value().first - this->_a * complex.get_value().second) / denom;
			return (Complex(a, b));
		}
		bool operator!=(const Complex &complex) const
		{
			if (this->_a == complex.get_value().first && this->_b == complex.get_value().second)
				return (false);
			return (true);
		}
		bool operator==(const int &value) const
		{
			if (value == 0 && this->_a == 0 && this->_b == 0)
				return (true);
			else if (this->_b == 0 && this->_a == value)
				return (true);
			return (false);
		}
		bool operator>(const Complex &complex) const
		{
			float magnitude_1 = std::pow(this->_a * this->_a + this->_b * this->_b, 0.5f);
			float magnitude_2 = std::pow(complex.get_value().first * complex.get_value().first + complex.get_value().second * complex.get_value().second, 0.5f);
			if (magnitude_1 > magnitude_2)
				return (true);
			return (false);
		}
		bool operator<(const Complex &complex) const
		{
			return (!(*this > complex));
		}

		std::pair<float, float> get_value(void) const;

	private:
		float _a;
		float _b;
};

std::ostream & operator << (std::ostream &, const Complex &);