/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/27 16:35:57 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "ui.h"

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
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static void	spawn_process(char *command, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execute_command(command, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	init_signal_handlers();
	save_terminal_configuration(&original_termios);
	while (true)
	{
		input = readline(PROMPT);
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		spawn_process(input, envp);
		add_history(input);
		free(input);
		restore_terminal_configuration(&original_termios);
	}
	return (EXIT_SUCCESS);
}
