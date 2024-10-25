/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:56:22 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "utils.h"

static void	discard_blanks(t_lexer *lexer)
{
	while (ft_isblank(*lexer->right))
		lexer->right++;
	lexer->left = lexer->right;
}

t_token_list	*process_blank(t_lexer *lexer)
{
	if (is_start_of_input(lexer))
	{
		discard_blanks(lexer);
		return (get_next_token(lexer));
	}
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_xstrndup(lexer->left, lexer->right - lexer->left);
		discard_blanks(lexer);
		return (construct_token(lexer->type, lexer->value));
	}
}
