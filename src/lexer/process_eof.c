/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:22:45 by yliu              #+#    #+#             */
/*   Updated: 2024/09/04 10:19:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*process_eof(t_lexer *lexer)
{
	if (is_start_of_input(lexer))
	{
		lexer->type = TOKEN_EOF;
		lexer->value = NULL;
	}
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_xstrndup(lexer->left, lexer->right - lexer->left);
		lexer->left = lexer->right;
	}
	return (construct_token(lexer->type, lexer->value));
}
