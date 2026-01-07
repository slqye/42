/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_formater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:18:42 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 14:49:51 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	lexer_formater(t_list **lexer)
{
	t_list	*holder;

	holder = *lexer;
	while (*lexer)
	{
		if (lexer_get_type(*lexer) == T_WORD && useless_quotes_case(lexer) != 0)
			return (1);
		if (lexer_get_type(*lexer) == T_WORD && clean_quotes_case(lexer) != 0)
			return (1);
		if (lexer_get_type(*lexer) == T_WORD)
			update_token_by_ascii(lexer_get_value(*lexer));
		*lexer = (*lexer)->next;
	}
	*lexer = holder;
	return (0);
}
