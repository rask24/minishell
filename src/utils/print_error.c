/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:20:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/01 22:57:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
