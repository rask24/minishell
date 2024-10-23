/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:11:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 15:28:54 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

static t_ast	*handle_syntax_error(t_ast *node, t_token_list **cur_token)
{
	const char	*token_value;

	token_value = get_token_value(*cur_token);
	if (token_value == NULL)
		token_value = "EOF";
	print_syntax_error(token_value);
	return (destroy_ast(node));
}

t_ast	*parser(t_token_list *token_list)
{
	t_ast			*node;
	t_token_list	**cur_token;

	cur_token = &token_list;
	node = parse_list(cur_token);
	if (node == NULL || get_token_type(*cur_token) != TOKEN_EOF)
		return (handle_syntax_error(node, cur_token));
	else if (node->type == AST_UNKNOWN)
		return (destroy_ast(node));
	return (node);
}
