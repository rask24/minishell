/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/10/08 20:35:02 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*process_quote(t_lexer *lexer)
{
	const char	*left_quote_ptr;
	char		*tmp;

	left_quote_ptr = lexer->right;
	lexer->right++;
	while (*lexer->right != *left_quote_ptr)
	{
		if (*lexer->right == '\0')
		{
			lexer->type = TOKEN_UNKNOWN;
			tmp = ft_xstrndup(left_quote_ptr, lexer->right - left_quote_ptr);
			lexer->value = tmp;
			return (construct_token(lexer->type, lexer->value));
		}
		lexer->right++;
	}
	lexer->right++;
	return (get_next_token(lexer));
}
