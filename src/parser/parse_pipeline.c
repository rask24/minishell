/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:18:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/25 14:15:41 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

t_ast	*push_pipe_node(t_ast *node, t_ast *new_node)
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
	if (node == NULL)
		return (NULL);
	while (get_token_type(*cur_token) == TOKEN_PIPE)
	{
		consume_token(cur_token);
		tmp = parse_command(cur_token);
		if (tmp == NULL)
		{
			destroy_ast(node);
			return (NULL);
		}
		node = push_pipe_node(node, tmp);
	}
	return (node);
}
