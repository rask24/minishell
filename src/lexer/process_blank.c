/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 22:48:05 by yliu             ###   ########.fr       */
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
		delimit_token(lexer);
	}
	else
	{
		lexer->value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
		lexer->type = TOKEN_WORD;
		_discard_blanks(lexer);
	}
}
