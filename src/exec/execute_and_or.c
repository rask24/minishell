/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:48 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/19 15:46:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ctx.h"
#include "exec_internal.h"

int	execute_and_or(t_ast *node, t_ctx *ctx)
{
	if (execute_ast_node(node->left, ctx, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((node->type == AST_AND && ctx->exit_status == EXIT_SUCCESS)
		|| (node->type == AST_OR && ctx->exit_status != EXIT_SUCCESS))
		return (execute_ast_node(node->right, ctx, NULL));
	return (EXIT_SUCCESS);
}
