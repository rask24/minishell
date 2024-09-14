/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:18:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/14 21:38:28 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

/*
** pipeline  :              simple_command
**           | pipeline '|' simple_command
**           ;
*/
t_ast	*parse_pipeline(t_token_list **cur_token)
{
	t_ast	*ast;

	ast = parse_simple_command(cur_token);
	if (ast == NULL)
		return (NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		if (get_token_type(*cur_token) != TOKEN_PIPE)
			break;
		if (!expect_token(cur_token, TOKEN_PIPE))
			return (handle_error(ast, get_token_value(*cur_token)));
		if (get_token_type(*cur_token) == TOKEN_EOF)
			return (handle_error(ast, get_token_value(*cur_token)));
		ast = construct_ast(AST_PIPE, ast, parse_simple_command(cur_token));
	}
	return (ast);
}
