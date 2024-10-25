/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:52 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/25 18:50:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

static bool	is_list_follow_set(t_token_list *cur_token)
{
	return (get_token_type(cur_token) == TOKEN_EOF
		|| get_token_type(cur_token) == TOKEN_AND_IF
		|| get_token_type(cur_token) == TOKEN_OR_IF
		|| get_token_type(cur_token) == TOKEN_R_PARENTHESIS);
}

/*
** list  :           pipeline
**       | list '&&' pipeline
**       | list '||' pipeline
**       ;
*/
t_ast	*parse_list(t_token_list **cur_token)
{
	t_ast			*node;
	t_ast			*tmp;
	t_ast_node_type	node_type;

	node = parse_pipeline(cur_token);
	if (node == NULL || node->type == AST_ABORT)
		return (node);
	while (true)
	{
		if (!is_list_follow_set(*cur_token))
			return (destroy_ast(node));
		node_type = (t_ast_node_type)get_token_type(*cur_token);
		if (!(node_type == AST_AND || node_type == AST_OR))
			break ;
		consume_token(cur_token);
		tmp = parse_pipeline(cur_token);
		if (tmp == NULL || tmp->type == AST_ABORT)
		{
			destroy_ast(node);
			return (tmp);
		}
		node = construct_ast(node_type, node, tmp);
	}
	return (node);
}
