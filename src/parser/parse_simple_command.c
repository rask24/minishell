/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/17 23:50:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

static bool	is_valid_head_token_simple_command(t_token_list **cur_token)
{
	return (get_token_type(*cur_token) == TOKEN_WORD
		|| is_redirect_token(get_token_type(*cur_token)));
}

static bool	try_parse_cmd_arg(t_ast *node, t_token_list **cur_token)
{
	push_cmd_arg(node, get_token_value(*cur_token));
	if (!consume_token(cur_token))
		return (destroy_and_return(node, cur_token, true));
	return (true);
}

/*
** simple_command  : cmd_prefix cmd_word cmd_suffix
**                 | cmd_prefix cmd_word
**                 | cmd_prefix
**                 |            cmd_word cmd_suffix
**                 |            cmd_word
**                 ;
*/
t_ast	*parse_simple_command(t_token_list **cur_token)
{
	t_ast					*node;
	t_parse_simple_commnad	parse_func;

	if (!is_valid_head_token_simple_command(cur_token))
		return (handle_syntax_error(NULL, get_token_value(*cur_token)));
	node = construct_ast(AST_COMMAND, NULL, NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		if (get_token_type(*cur_token) == TOKEN_WORD)
			parse_func = try_parse_cmd_arg;
		else if (is_redirect_token(get_token_type(*cur_token)))
			parse_func = try_parse_redirect;
		else
			break ;
		if (!parse_func(node, cur_token))
			return (NULL);
	}
	return (node);
}
