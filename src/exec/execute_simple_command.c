/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:18:33 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/13 17:35:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "libft.h"
#include "ui.h"
#include "utils.h"

static char	**convert_list_to_array(t_list *cmd_args)
{
	char	**argv;
	int		i;

	argv = ft_xmalloc(sizeof(char *) * (ft_lstsize(cmd_args) + 1));
	i = 0;
	while (cmd_args != NULL)
	{
		argv[i] = cmd_args->content;
		cmd_args = cmd_args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static void	handle_pipeline(t_pipeline_info *info)
{
	if (info->fd_in != STDIN_FILENO)
	{
		if (dup2(info->fd_in, STDIN_FILENO) == -1)
			print_error("dup2", strerror(errno));
		close(info->fd_in);
	}
	if (info->fd_out != STDOUT_FILENO)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) == -1)
			print_error("dup2", strerror(errno));
		close(info->fd_out);
	}
}

pid_t	execute_simple_command(t_ast *cmd_node, char **envp,
			t_pipeline_info *info)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", strerror(errno));
		return (-1);
	}
	if (pid == 0)
	{
		argv = convert_list_to_array(cmd_node->cmd_args);
		handle_pipeline(info);
		if (handle_redirects(cmd_node->redirects) == -1)
			exit(EXIT_FAILURE);
		reset_signal_handlers();
		if (execve(argv[0], argv, envp) == -1)
		{
			print_error("execve", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}
