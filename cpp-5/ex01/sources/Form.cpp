/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:37:59 by slaye             #+#    #+#             */
/*   Updated: 2024/07/04 15:22:59 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Form::Form(void) : _name("Default"), _is_signed(false), _g_sign(150), _g_exec(150)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Form::Form(const std::string name, unsigned int g_sign, unsigned int g_exec) : _name(name), _is_signed(false), _g_sign(g_sign), _g_exec(g_exec)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	unsigned int sign = g_sign;
	unsigned int exec = g_exec;
	if (sign < 1 || exec < 1)
		throw Form::GradeTooHighException();
	else if (sign > 150 || exec > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const &ref) : _name(ref.getName()), _is_signed(ref.getStatus()), _g_sign(ref.getGradeSign()), _g_exec(ref.getGradeExec())
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	*this = ref;
}

Form::~Form(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Form	&Form::operator=(Form const &ref)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	(void) ref;
	return (*this);
}

const std::string	Form::getName(void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return (this->_name);
}

bool	Form::getStatus(void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return (this->_is_signed);
}

unsigned int	Form::getGradeSign(void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return (this->_g_sign);
}

unsigned int	Form::getGradeExec(void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return (this->_g_exec);
}

void	Form::beSigned(Bureaucrat &ref)
{
	if (ref.getGrade() > this->getGradeSign())
		throw Form::GradeTooLowException();
	else
		this->_is_signed = true;
}

std::ostream	&operator<<(std::ostream &stream, Form const &ref)
{
	stream << "Name: " << ref.getName() << "\nStatus: " << ref.getStatus() << "\nSign grade: " << ref.getGradeSign() << "\nExec grade: " << ref.getGradeExec();
	return (stream);
}

const char	*Form::GradeTooLowException::what() const throw()
{
	return ("Grade too low");
}

const char	*Form::GradeTooHighException::what() const throw()
{
	return ("Grade too high");
}