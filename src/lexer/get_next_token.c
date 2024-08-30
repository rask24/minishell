/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:52:15 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:58:23 by yliu             ###   ########.fr       */
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
		if (*lexer->right == '\0')
		{
			token_value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
			lexer->left = lexer->right;
			return (construct_token(TOKEN_WORD, token_value));
		}
		if (is_quote_char(*lexer->right))
			process_quote(lexer, *lexer->right);
		if (ft_isspace(*lexer->right))
			return (process_blank(lexer));
		lexer->right++;
	}
}
