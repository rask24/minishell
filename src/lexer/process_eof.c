/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:22:45 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 22:52:43 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_eof(t_lexer *lexer)
{
	if (is_start_of_input(lexer))
	{
		lexer->type = TOKEN_EOF;
		lexer->value = NULL;
	}
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_strndup(lexer->left, lexer->right - lexer->left);
		lexer->left = lexer->right;
	}
}
