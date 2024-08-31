/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:37 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 16:42:43 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void	discards_chars(t_lexer *lexer, int n)
{
	lexer->right += n;
	lexer->left = lexer->right;
}

void	process_operator(t_lexer *lexer)
{
	if (lexer->right == lexer->left)
	{
		if (ft_strncmp("|", lexer->right, 1) == 0)
		{
			lexer->type = TOKEN_PIPE;
			lexer->value = ft_strndup(lexer->right, 1);
			discards_chars(lexer, 1);
		}
	}
	else
	{
		lexer->value = ft_strndup(lexer->left, lexer->right - lexer->left);
		lexer->type = TOKEN_WORD;
		lexer->left = lexer->right;
	}
}
