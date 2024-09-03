/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 23:09:05 by yliu              #+#    #+#             */
/*   Updated: 2024/09/03 17:49:43 by yliu             ###   ########.fr       */
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

void	delimit_input(t_lexer *lexer)
{
	while (true)
	{
		if (_is_quote_char(*lexer->right))
			process_quote(lexer);
		else if (*lexer->right == '\0')
			return (process_eof(lexer));
		else if (ft_isblank(*lexer->right))
			return (process_blank(lexer));
		else if (_is_operator_char(*lexer->right))
			return (process_operator(lexer));
		else if (*lexer->right == '#' && is_start_of_input(lexer))
			return (process_comment(lexer));
		lexer->right++;
	}
}
