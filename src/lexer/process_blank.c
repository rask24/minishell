/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/09/04 10:24:06 by yliu             ###   ########.fr       */
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

t_token_list	*process_blank(t_lexer *lexer)
{
	if (is_start_of_input(lexer))
	{
		_discard_blanks(lexer);
		return(get_next_token(lexer));
	}
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_xstrndup(lexer->left, lexer->right - lexer->left);
		_discard_blanks(lexer);
		return (construct_token(lexer->type, lexer->value));
	}
}
