/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:37 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 22:43:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void	_discards_operator(t_lexer *lexer, int n)
{
	lexer->right += n;
	lexer->left = lexer->right;
}

static void	_update_lexer(t_lexer *lexer, t_token_type type, size_t length)
{
	lexer->type = type;
	lexer->value = ft_xstrndup(lexer->left, length);
	_discards_operator(lexer, length);
}

static void	process_operator_type(t_lexer *lexer)
{
	if (ft_strncmp("&&", lexer->right, 2) == 0)
		_update_lexer(lexer, TOKEN_AND_IF, 2);
	else if (ft_strncmp("||", lexer->right, 2) == 0)
		_update_lexer(lexer, TOKEN_OR_IF, 2);
	else if (ft_strncmp("(", lexer->right, 1) == 0)
		_update_lexer(lexer, TOKEN_L_PARENTHESIS, 1);
	else if (ft_strncmp(")", lexer->right, 1) == 0)
		_update_lexer(lexer, TOKEN_R_PARENTHESIS, 1);
	else if (ft_strncmp("|", lexer->right, 1) == 0)
		_update_lexer(lexer, TOKEN_PIPE, 1);
	else if (ft_strncmp("<<", lexer->right, 2) == 0)
		_update_lexer(lexer, TOKEN_DLESS, 2);
	else if (ft_strncmp("<", lexer->right, 1) == 0)
		_update_lexer(lexer, TOKEN_LESS, 1);
	else if (ft_strncmp(">>", lexer->right, 2) == 0)
		_update_lexer(lexer, TOKEN_DGREAT, 2);
	else if (ft_strncmp(">", lexer->right, 1) == 0)
		_update_lexer(lexer, TOKEN_GREAT, 1);
}

static bool	is_single_ampersand(t_lexer *lexer)
{
	return (*lexer->right == '&' && *(lexer->right + 1) != '&');
}

t_token_list	*process_operator(t_lexer *lexer)
{
	if (is_single_ampersand(lexer))
		return (process_word(lexer));
	if (is_start_of_input(lexer))
		process_operator_type(lexer);
	else
	{
		lexer->type = TOKEN_WORD;
		lexer->value = ft_xstrndup(lexer->left, lexer->right - lexer->left);
		lexer->left = lexer->right;
	}
	return (construct_token(lexer->type, lexer->value));
}
