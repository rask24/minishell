/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:52:15 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:53:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static bool	is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

t_token_list	*get_next_token(t_lexer *lexer)
{
	char	*token_value;

	while (true)
	{
		if (*lexer->end == '\0')
		{
			token_value = ft_substr(lexer->start, 0, lexer->end - lexer->start);
			lexer->start = lexer->end;
			return (construct_token(TOKEN_WORD, token_value));
		}
		if (is_quote_char(*lexer->end))
			process_quote(lexer, *lexer->end);
		if (ft_isspace(*lexer->end))
			return (process_blank(lexer));
		lexer->end++;
	}
}
