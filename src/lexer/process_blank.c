/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 13:34:19 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_blank(t_lexer *lexer)
{
	if (lexer->right == lexer->left)
	{
		while (ft_isblank(*lexer->right))
		{
			lexer->right++;
		}
		lexer->left = lexer->right;
		delimit_token(lexer);
	}
	else
	{
		lexer->value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
		lexer->type = TOKEN_WORD;
		while (ft_isblank(*lexer->right))
		{
			lexer->right++;
		}
		lexer->left = lexer->right;
	}
}
