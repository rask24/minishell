/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/07 03:02:58 by reasuke          ###   ########.fr       */
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

// TODO: Handle casting from t_token_type to t_redirect_type
t_ast	*parse_simple_command(t_token_list **cur_token)
{
	t_ast			*ast;
	t_redirect_info	redirect_info;

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
			redirect_info.type = (t_redirect_type)get_token_type(*cur_token);
			expect_token(cur_token, (t_token_type)redirect_info.type);
			redirect_info.filepath = get_token_value(*cur_token);
			expect_token(cur_token, TOKEN_WORD);
			push_redirect_info(ast, &redirect_info);
		}
	}
	return (ast);
}
