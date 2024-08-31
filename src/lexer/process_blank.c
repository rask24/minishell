/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 23:08:08 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void	_discard_blanks(t_lexer *lexer)
{
	while (ft_isblank(*lexer->right))
	{
		lexer->right++;
	}
	lexer->left = lexer->right;
}

void	process_blank(t_lexer *lexer)
{
	if (is_start_of_input(lexer))
	{
		_discard_blanks(lexer);
		delmit_input(lexer);
	}
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_strndup(lexer->left, lexer->right - lexer->left);
		_discard_blanks(lexer);
	}
}
