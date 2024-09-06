/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/07 02:37:20 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

bool	_is_redirect_token(t_token_type type)
{
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

// TODO: Replace the second argument of push_redirect_info
t_ast	*parse_simple_command(t_token_list **cur_token)
{
	t_ast			*ast;
	t_token_type	token_type;
	const char		*filepath;

	(void)cur_token;
	ast = construct_ast(AST_COMMAND, NULL, NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		if (get_token_type(*cur_token) == TOKEN_WORD)
		{
			push_cmd_arg(ast, get_token_value(*cur_token));
			expect_token(cur_token, TOKEN_WORD);
		}
		else if (_is_redirect_token(get_token_type(*cur_token)))
		{
			token_type = get_token_type(*cur_token);
			expect_token(cur_token, token_type);
			filepath = get_token_value(*cur_token);
			expect_token(cur_token, TOKEN_WORD);
			push_redirect_info(ast,
				&(t_redirect_info){(t_redirect_type)token_type, filepath});
		}
	}
	return (ast);
}
