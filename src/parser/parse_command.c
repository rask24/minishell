/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:19:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 00:56:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

static bool	is_command_follow_set(t_token_list *cur_token)
{
	return (get_token_type(cur_token) == TOKEN_EOF
		|| get_token_type(cur_token) == TOKEN_AND_IF
		|| get_token_type(cur_token) == TOKEN_OR_IF
		|| get_token_type(cur_token) == TOKEN_PIPE
		|| get_token_type(cur_token) == TOKEN_R_PARENTHESIS);
}

/*
** command  : simple_command
**          : '(' list ')'
**          : '(' list ')' redirect_list
**          ;
*/
t_ast	*parse_command(t_token_list **cur_token)
{
	t_ast	*node;
	t_ast	*tmp;

	if (get_token_type(*cur_token) != TOKEN_L_PARENTHESIS)
		return (parse_simple_command(cur_token));
	consume_token(cur_token);
	tmp = parse_list(cur_token);
	if (tmp == NULL)
		return (NULL);
	node = construct_ast(AST_SUBSHELL, tmp, NULL);
	if (get_token_type(*cur_token) != TOKEN_R_PARENTHESIS)
		return (destroy_ast(node));
	consume_token(cur_token);
	while (true)
	{
		if (is_command_follow_set(*cur_token))
			break ;
		if (!is_redirect_first_set(*cur_token))
			return (destroy_ast(node));
		if (!try_parse_redirect(node, cur_token))
			return (destroy_ast(node));
	}
	return (node);
}
