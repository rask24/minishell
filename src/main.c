/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/23 21:37:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "ui.h"

static void	execute_command(char *complete_commnad, char **envp)
{
	char	**argv;

	argv = ft_xmalloc(sizeof(char *) * 3);
	argv[0] = "sh";
	argv[1] = "-c";
	argv[2] = complete_commnad;
	reset_signal_handlers();
	if (execve("/bin/sh", argv, envp) == -1)
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
	}
	return (EXIT_SUCCESS);
}
