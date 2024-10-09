/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/10/09 11:57:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"
#include "ctx.h"
#include "env.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

static bool	is_valid_last_token(t_token_list *last_token)
{
	if (last_token == NULL)
		return (false);
	if (get_token_type(last_token) == TOKEN_UNTERMINATED_QUOTE)
	{
		print_error("unterminated quote", get_token_value(last_token));
		return (false);
	}
	if (get_token_type(last_token) == TOKEN_UNKNOWN)
	{
		print_error("unknown token", get_token_value(last_token));
		return (false);
	}
	return (true);
}

int	execute_ast_node(t_ast *node, t_ctx *ctx, t_pipeline_conf *conf)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	else if (node->type == AST_COMMAND)
		return (execute_command(node, ctx, conf));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, ctx, conf));
	else if (node->type == AST_AND || node->type == AST_OR)
		return (execute_and_or(node, ctx, conf));
	else
		return (EXIT_FAILURE);
}

void	exec(char *input, t_ctx *ctx)
{
	t_token_list	*token_list;
	t_ast			*node;
	t_pipeline_conf	conf;

	token_list = lexer(input);
	if (is_valid_last_token(ft_lstlast(token_list)) == false)
	{
		destroy_token_list(token_list);
		return ;
	}
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	conf = (t_pipeline_conf){.fd_in = STDIN_FILENO, .fd_out = STDOUT_FILENO};
	if (execute_ast_node(node, ctx, &conf) == EXIT_FAILURE)
		print_error(__func__, "failed to execute command");
	destroy_token_list(token_list);
	destroy_ast(node);
}
