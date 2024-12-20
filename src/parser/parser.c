/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:11:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/25 19:03:08 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ast.h"
#include "ctx.h"
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

static bool	has_abort_node(t_ast *node)
{
	if (node == NULL)
		return (false);
	if (node->type == AST_ABORT)
		return (true);
	if (node->left && has_abort_node(node->left))
		return (true);
	if (node->right && has_abort_node(node->right))
		return (true);
	return (false);
}

t_ast	*parser(t_token_list *token_list, t_ctx *ctx)
{
	t_ast			*node;
	t_token_list	**cur_token;

	cur_token = &token_list;
	node = parse_list(cur_token);
	if (has_abort_node(node))
	{
		ctx->exit_status = 128 + SIGINT;
		return (destroy_ast(node));
	}
	else if (node == NULL || get_token_type(*cur_token) != TOKEN_EOF)
	{
		ctx->exit_status = 2;
		return (handle_syntax_error(node, cur_token));
	}
	return (node);
}
