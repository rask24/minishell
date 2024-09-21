/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:52 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/18 13:47:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

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
	if (node == NULL)
		return (NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		node_type = (t_ast_node_type)get_token_type(*cur_token);
		if (node_type != AST_AND && node_type != AST_OR)
			break ;
		consume_token(cur_token);
		tmp = parse_pipeline(cur_token);
		if (tmp == NULL)
			return (NULL);
		node = construct_ast(node_type, node, tmp);
	}
	return (node);
}
