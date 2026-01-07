/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:29:24 by slaye             #+#    #+#             */
/*   Updated: 2024/07/04 14:59:12 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class Bureaucrat;

class Form {
	public:
		Form(void); // canonical
		Form(Form const &ref); // canonical
		virtual ~Form(void); // canonical

		Form(const std::string name, unsigned int g_sign, unsigned int g_exec);
		Form					&operator=(Form const &ref); // canonical
		const std::string		getName(void) const;
		bool					getStatus(void) const;
		unsigned int		getGradeSign(void) const;
		unsigned int		getGradeExec(void) const;
		void					beSigned(Bureaucrat &ref);

		class GradeTooLowException : public std::exception {
			public:
				virtual const char	*what() const throw();
		};
		class GradeTooHighException : public std::exception {
			public:
				virtual const char	*what() const throw();
		};
	private:
		const std::string	_name;
		bool				_is_signed;
		const unsigned int	_g_sign;
		const unsigned int	_g_exec;
};

std::ostream	&operator<<(std::ostream &stream, Form const &ref);