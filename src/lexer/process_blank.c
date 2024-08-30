/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:58:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void	discard_char(t_lexer *lexer)
{
	lexer->left++;
	lexer->right++;
}

t_token_list	*process_blank(t_lexer *lexer)
{
	char	*token_value;

	if (lexer->left == lexer->right)
	{
		discard_char(lexer);
		return (NULL);
	}
	token_value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
	while (ft_isspace(*lexer->right))
	{
		lexer->right++;
	}
	lexer->left = lexer->right;
	return (construct_token(TOKEN_WORD, token_value));
}
