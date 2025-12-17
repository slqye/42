#include "Span.hpp"

Span::Span(void) : _n(0)
{
}

Span::Span(unsigned int n) : _n(n)
{
}

Span::Span(const Span &reference) : _n(reference._n), _container(reference._container)
{
}

Span::~Span(void)
{
}

Span	&Span::operator=(const Span &reference)
{
	this->_n = reference._n;
	this->_container = reference._container;
	return (*this);
}

void	Span::addNumber(int number)
{
	if (this->_container.size() < this->_n)
		this->_container.push_back(number);
	else
		throw Span::CapacityException();
}

unsigned int	Span::shortestSpan(void) const
{
	std::vector<int>	holder = this->_container;
	int					result;

	if (this->_container.size() < 2)
		throw Span::DistanceException();
	std::sort(holder.begin(), holder.end());
	result = holder[1] - holder[0];
	for (unsigned int i = 1; i < holder.size() - 1; i++)
	{
		if (holder[i + 1] - holder[i] < result)
			result = holder[i + 1] - holder[i];
	}
	return (result);
}

unsigned int	Span::longestSpan(void) const
{
	unsigned int	max;
	unsigned int	min;

	if (this->_container.size() < 2)
		throw Span::DistanceException();
	max = *std::max_element(this->_container.begin(), this->_container.end());
	min = *std::min_element(this->_container.begin(), this->_container.end());
	return (max - min);
}

const char	*Span::CapacityException::what() const throw()
{
	return ("Span already full.");
}

const char	*Span::DistanceException::what() const throw()
{
	return ("Span does not have the required number od items.");
}