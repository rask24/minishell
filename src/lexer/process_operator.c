/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:37 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 17:46:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void	discards_chars(t_lexer *lexer, int n)
{
	lexer->right += n;
	lexer->left = lexer->right;
}

static void	update_lexer(t_lexer *lexer, t_token_type type, size_t length)
{
	lexer->type = type;
	lexer->value = ft_strndup(lexer->left, length);
	discards_chars(lexer, length);
}

void	process_operator(t_lexer *lexer)
{
	if (lexer->right == lexer->left)
	{
		if (ft_strncmp("&&", lexer->right, 2) == 0)
			update_lexer(lexer, TOKEN_AND_IF, 2);
		else if (ft_strncmp("||", lexer->right, 2) == 0)
			update_lexer(lexer, TOKEN_OR_IF, 2);
		else if (ft_strncmp("(", lexer->right, 1) == 0)
			update_lexer(lexer, TOKEN_L_PARENTHESIS, 1);
		else if (ft_strncmp(")", lexer->right, 1) == 0)
			update_lexer(lexer, TOKEN_R_PARENTHESIS, 1);
		else if (ft_strncmp("|", lexer->right, 1) == 0)
			update_lexer(lexer, TOKEN_PIPE, 1);
		else if (ft_strncmp("<<", lexer->right, 2) == 0)
			update_lexer(lexer, TOKEN_DLESS, 2);
		else if (ft_strncmp("<", lexer->right, 1) == 0)
			update_lexer(lexer, TOKEN_LESS, 1);
		else if (ft_strncmp(">>", lexer->right, 2) == 0)
			update_lexer(lexer, TOKEN_DGREAT, 2);
		else if (ft_strncmp(">", lexer->right, 1) == 0)
			update_lexer(lexer, TOKEN_GREAT, 1);
	}
	else
	{
		lexer->value = ft_strndup(lexer->left, lexer->right - lexer->left);
		lexer->type = TOKEN_WORD;
		lexer->left = lexer->right;
	}
}
