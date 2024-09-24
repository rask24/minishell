/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 16:09:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "env.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	wait_for_children(pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

int	execute_ast_node(t_ast *node, t_env_list *env_list, t_pipeline_conf *conf)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	else if (node->type == AST_COMMAND)
		return (execute_command(node, env_list, conf));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, env_list, conf));
	else
		return (EXIT_FAILURE);
}

void	exec(char *input, t_env_list *env_list)
{
	t_token_list	*token_list;
	t_ast			*node;
	t_pipeline_conf	conf;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	conf = (t_pipeline_conf){.fd_in = STDIN_FILENO, .fd_out = STDOUT_FILENO,
		.pipe_read = -1, .pipe_write = -1, .is_last = true};
	if (execute_ast_node(node, env_list, &conf) == EXIT_FAILURE)
		print_error("exec", "unsupported AST type");
	destroy_token_list(token_list);
	destroy_ast(node);
}
