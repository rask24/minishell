/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/14 23:33:24 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	exec(char *input, char **envp)
{
	t_token_list	*token_list;
	t_ast			*node;
	pid_t			last_pid;
	int				status;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	if (node->type == AST_PIPE || node->type == AST_COMMAND)
	{
		last_pid = execute_pipeline(node, envp, STDIN_FILENO, STDOUT_FILENO);
		waitpid(last_pid, &status, 0);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	else
		print_error("exec", "unsupported AST type");
	destroy_token_list(token_list);
	destroy_ast(node);
}
