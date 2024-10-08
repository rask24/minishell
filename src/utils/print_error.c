/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:20:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/27 01:14:40 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
** Using printf for line buffering
** instead of ft_dprintf (not supporting line buffering)
** Emulates dprintf-like behavior using dup and dup2 to redirect stdout to sterr
*/
void	print_error(const char *func, const char *desc)
{
	int	stdout_fd;
	int	res;

	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd == -1)
	{
		perror("minishell: dup");
		return ;
	}
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(stdout_fd);
		return ;
	}
	res = printf("minishell: %s: %s\n", func, desc);
	if (res < 0)
		perror("minishell: printf");
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	close(stdout_fd);
}

void	print_error_exit(const char *func, const char *desc, int exit_status)
{
	print_error(func, desc);
	exit(exit_status);
}

void	print_syntax_error(const char *token_value)
{
	int	stdout_fd;
	int	res;

	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd == -1)
	{
		perror("minishell: dup");
		return ;
	}
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(stdout_fd);
		return ;
	}
	res = printf("minishell: syntax error near unexpected token `%s'\n",
			token_value);
	if (res < 0)
		perror("minishell: printf");
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	close(stdout_fd);
}

void	print_heredoc_warning(const char *delimiter)
{
	int		stdout_fd;
	int		res;

	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd == -1)
	{
		perror("minishell: dup");
		return ;
	}
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(stdout_fd);
		return ;
	}
	res = printf("%s: %s: %s`%s')\n",
			"minishell", "warning",
			"here-document delimited by end-of-file (wanted ", delimiter);
	if (res < 0)
		perror("minishell: printf");
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	close(stdout_fd);
}
