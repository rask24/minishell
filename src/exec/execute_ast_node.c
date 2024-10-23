/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/10/19 16:25:14 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exec_internal.h"

int	execute_ast_node(t_ast *node, t_ctx *ctx, t_pipe_conf *conf)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	else if (node->type == AST_COMMAND)
		return (execute_command(node, ctx, conf));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, ctx));
	else if (node->type == AST_AND || node->type == AST_OR)
		return (execute_and_or(node, ctx));
	else if (node->type == AST_SUBSHELL)
		return (execute_subshell(node, ctx, conf));
	else
		return (EXIT_FAILURE);
}
