/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:52:15 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 14:05:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static bool	is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

void delimit_token(t_lexer *lexer)
{
	while (true)
	{
		if (*lexer->right == '\0')
		{
			if (lexer->left == lexer->right)
			{
				lexer->value = NULL;
				lexer->type = TOKEN_EOF;
			} else {
				lexer->value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
				lexer->type = TOKEN_WORD;
				lexer->left = lexer->right;
			}
			break;
		}
		else if (is_quote_char(*lexer->right))
		{
			process_quote(lexer, *lexer->right);
		}
		else if (ft_isblank(*lexer->right))
		{
			process_blank(lexer);
			break;
		}
		lexer->right++;
	}
}

t_token_list	*get_next_token(t_lexer *lexer)
{
	delimit_token(lexer);
	return (construct_token(lexer->type, lexer->value));
}
