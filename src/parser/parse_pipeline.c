/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:18:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/25 16:00:14 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

static bool	is_pipeline_follow_set(t_token_list *cur_token)
{
	return (get_token_type(cur_token) == TOKEN_EOF
		|| get_token_type(cur_token) == TOKEN_AND_IF
		|| get_token_type(cur_token) == TOKEN_OR_IF
		|| get_token_type(cur_token) == TOKEN_PIPE
		|| get_token_type(cur_token) == TOKEN_R_PARENTHESIS);
}

static t_ast	*push_pipe_node(t_ast *node, t_ast *new_node)
{
	if (node == NULL || new_node == NULL)
		return (NULL);
	if (node->type != AST_PIPE)
		return (construct_ast(AST_PIPE, node, new_node));
	node->right = push_pipe_node(node->right, new_node);
	return (node);
}

/*
** pipeline  :              command
**           : pipeline '|' command
**           ;
*/
t_ast	*parse_pipeline(t_token_list **cur_token)
{
	t_ast	*node;
	t_ast	*tmp;

	node = parse_command(cur_token);
	if (node == NULL || node->type == AST_ABORT)
		return (node);
	while (true)
	{
		if (!is_pipeline_follow_set(*cur_token))
			return (destroy_ast(node));
		if (get_token_type(*cur_token) != TOKEN_PIPE)
			break ;
		consume_token(cur_token);
		tmp = parse_command(cur_token);
		if (tmp == NULL)
			return (destroy_ast(node));
		else if (tmp->type == AST_ABORT)
			return (tmp);
		node = push_pipe_node(node, tmp);
	}
	return (node);
}
