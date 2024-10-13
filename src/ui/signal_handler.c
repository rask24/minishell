/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:03:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/13 22:39:11 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"
#include "readline/readline.h"
#include "utils.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal_handlers(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
}

void	reset_signal_handlers(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
}
