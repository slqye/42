/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:29:24 by slaye             #+#    #+#             */
/*   Updated: 2024/07/02 15:38:01 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class Bureaucrat;

class AForm {
	public:
		AForm(void); // canonical
		AForm(AForm const &ref); // canonical
		virtual ~AForm(void); // canonical

		AForm(const std::string name, unsigned int g_sign, unsigned int g_exec);
		AForm			&operator=(AForm const &ref); // canonical
		const std::string	getName(void) const;
		bool			getStatus(void) const;
		unsigned int	getGradeSign(void) const;
		unsigned int	getGradeExec(void) const;
		void			beSigned(Bureaucrat &ref);
		virtual void	execute(Bureaucrat const & executor) const = 0;

		class GradeTooLowException : public std::exception {
			public:
				virtual const char	*what() const throw();
		};
		class GradeTooHighException : public std::exception {
			public:
				virtual const char	*what() const throw();
		};
		class NotSignedException : public std::exception {
			public:
				virtual const char	*what() const throw();
		};
	private:
		const std::string	_name;
		bool				_is_signed;
		const unsigned int	_g_sign;
		const unsigned int	_g_exec;
};

std::ostream	&operator<<(std::ostream &stream, AForm const &ref);