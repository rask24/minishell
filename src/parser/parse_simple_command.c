/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 15:26:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

static bool	is_simple_command_first_set(t_token_list **cur_token)
{
	return (get_token_type(*cur_token) == TOKEN_WORD
		|| is_redirect_token(get_token_type(*cur_token)));
}

static bool	is_simple_command_follow_set(t_token_list *cur_token)
{
	return (get_token_type(cur_token) == TOKEN_EOF
		|| get_token_type(cur_token) == TOKEN_AND_IF
		|| get_token_type(cur_token) == TOKEN_OR_IF
		|| get_token_type(cur_token) == TOKEN_PIPE
		|| get_token_type(cur_token) == TOKEN_R_PARENTHESIS);
}

static t_parse_status	try_parse_cmd_arg(t_ast *node, t_token_list **cur_token)
{
	push_cmd_arg(node, get_token_value(*cur_token));
	return (consume_token(cur_token));
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
	t_ast			*node;
	t_try_parse		parse_func;
	t_parse_status	status;

	if (!is_simple_command_first_set(cur_token))
		return (NULL);
	node = construct_ast(AST_COMMAND, NULL, NULL);
	while (true)
	{
		if (is_simple_command_follow_set(*cur_token))
			break ;
		if (get_token_type(*cur_token) == TOKEN_WORD)
			parse_func = try_parse_cmd_arg;
		else if (is_redirect_token(get_token_type(*cur_token)))
			parse_func = try_parse_redirect;
		else
			return (destroy_ast(node));
		status = parse_func(node, cur_token);
		if (status == PARSE_FAILURE)
			return (destroy_ast(node));
		else if (status == PARSE_ABORT)
		{
			destroy_ast(node);
			return (construct_ast(AST_UNKNOWN, NULL, NULL));
		}
	}
	return (node);
}
