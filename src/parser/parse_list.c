/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:52 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/14 23:23:40 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

static t_ast_node_type	convert_token_to_node(t_token_type token_type)
{
	if (token_type == TOKEN_AND_IF)
		return (AST_AND);
	else if (token_type == TOKEN_OR_IF)
		return (AST_OR);
	return (AST_UNKNOWN);
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
	t_ast_node_type	node_type;

	node = parse_pipeline(cur_token);
	if (node == NULL)
		return (NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		node_type = convert_token_to_node(get_token_type(*cur_token));
		if (node_type != AST_AND && node_type != AST_OR)
			return (handle_error(node, get_token_value(*cur_token)));
		consume_token(cur_token);
		if (get_token_type(*cur_token) == TOKEN_EOF)
			return (handle_error(node, get_token_value(*cur_token)));
		node = construct_ast(node_type, node, parse_pipeline(cur_token));
	}
	return (node);
}
