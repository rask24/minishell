/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:47:11 by yliu              #+#    #+#             */
/*   Updated: 2024/10/19 20:47:42 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*process_newline(t_lexer *lexer)
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
