/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:22:17 by slaye             #+#    #+#             */
/*   Updated: 2024/05/15 12:51:58 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

class Contact
{
	public:
		Contact();
		~Contact(void);
		int		setup(void);
		void	print(void) const;
		std::string	get_fname(void) const;
		std::string	get_lname(void) const;
		std::string	get_nickname(void) const;
		std::string	get_number(void) const;
		std::string	get_secret(void) const;
		
	private:
		bool	is_strnum(std::string value) const;
		bool	is_empty(std::string value) const;
		std::string	fname;
		std::string	lname;
		std::string	nickname;
		std::string	number;
		std::string	secret;
};

#endif