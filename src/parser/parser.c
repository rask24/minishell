/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:11:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 17:34:08 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ast.h"
#include "ctx.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

static t_ast	*handle_syntax_error(t_ast *node, t_token_list **cur_token,
					t_ctx *ctx)
{
	const char	*token_value;

	token_value = get_token_value(*cur_token);
	if (token_value == NULL)
		token_value = "EOF";
	print_syntax_error(token_value);
	ctx->exit_status = 2;
	return (destroy_ast(node));
}

t_ast	*parser(t_token_list *token_list, t_ctx *ctx)
{
	t_ast			*node;
	t_token_list	**cur_token;

	cur_token = &token_list;
	node = parse_list(cur_token);
	if (node == NULL || get_token_type(*cur_token) != TOKEN_EOF)
		return (handle_syntax_error(node, cur_token, ctx));
	else if (node->type == AST_UNKNOWN)
	{
		ctx->exit_status = 128 + SIGINT;
		return (destroy_ast(node));
	}
	return (node);
}
