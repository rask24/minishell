/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/10/27 17:36:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_internal.h"
#include "token.h"

static void	construct_lexer_info(const char *input, t_lexer *lexer)
{
	lexer->left = input;
	lexer->right = input;
	lexer->value = NULL;
	lexer->type = -1;
}

t_token_list	*lexer(const char *input)
{
	t_token_list	*one_token;
	t_token_list	*token_list;
	t_lexer			lexer;

	token_list = NULL;
	construct_lexer_info(input, &lexer);
	while (true)
	{
		one_token = get_next_token(&lexer);
		ft_lstadd_back(&token_list, one_token);
		if (get_token_type(one_token) == TOKEN_EOF
			|| get_token_type(one_token) == TOKEN_UNTERMINATED_QUOTE
			|| get_token_type(one_token) == TOKEN_UNKNOWN)
			break ;
	}
	return (token_list);
}
