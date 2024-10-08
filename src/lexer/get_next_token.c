/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:52:15 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 22:36:51 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static bool	_is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static bool	_is_operator_char(char c)
{
	return (c == '|' || c == '&'
		|| c == '<' || c == '>'
		|| c == '(' || c == ')');
}

t_token_list	*get_next_token(t_lexer *lexer)
{
	if (*lexer->right == '\0')
		return (process_eof(lexer));
	else if (ft_isblank(*lexer->right))
		return (process_blank(lexer));
	else if (_is_operator_char(*lexer->right))
		return (process_operator(lexer));
	else if (*lexer->right == '#' && is_start_of_input(lexer))
		return (process_comment(lexer));
	else if (_is_quote_char(*lexer->right))
		return (process_quote(lexer));
	else
		return (process_word(lexer));
}
