/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/06 14:32:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static void	execute_command(char *complete_command, char **envp)
{
	char	*argv[4];

	argv[0] = "bash";
	argv[1] = "-c";
	argv[2] = complete_command;
	argv[3] = NULL;
	reset_signal_handlers();
	if (execve("/bin/bash", argv, envp) == -1)
	{
		print_error("execve", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	spawn_process(char *command, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execute_command(command, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}
