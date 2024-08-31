/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:52:15 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 22:48:05 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static bool	_is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static bool	_is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

void	delimit_token(t_lexer *lexer)
{
	while (true)
	{
		if (_is_quote_char(*lexer->right))
			process_quote(lexer);
		if (*lexer->right == '\0')
			return (process_eof(lexer));
		else if (ft_isblank(*lexer->right))
			return (process_blank(lexer));
		else if (_is_operator_char(*lexer->right))
			return (process_operator(lexer));
		else if (is_start_of_input(lexer) && *lexer->right == '#')
			return (process_comment(lexer));
		lexer->right++;
	}
}

t_token_list	*get_next_token(t_lexer *lexer)
{
	delimit_token(lexer);
	return (construct_token(lexer->type, lexer->value));
}
