/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/23 19:59:47 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "ui.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	init_signal_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	execute_command(char *complete_commnad, char **envp)
{
	char	**argv;

	argv = ft_xmalloc(sizeof(char *) * 3);
	argv[0] = "sh";
	argv[1] = "-c";
	argv[2] = complete_commnad;
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
	char	*input;

	(void)argc;
	(void)argv;
	init_signal_handler();
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
