/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:03:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/24 22:28:17 by reasuke          ###   ########.fr       */
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

volatile sig_atomic_t g_signum = 0;

static void	set_signum(int sig)
{
	g_signum = sig;
}

static int	setup_sigaction(int signum, void (*handler)(int))
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	return sigaction(signum, &sa, NULL);
}

void	init_signal_handlers(void)
{
	if (setup_sigaction(SIGINT, set_signum) == -1)
		print_error("sigaction", strerror(errno));
	if (setup_sigaction(SIGQUIT, SIG_IGN) == -1)
		print_error("sigaction", strerror(errno));
	if (setup_sigaction(SIGTSTP, SIG_IGN) == -1)
		print_error("sigaction", strerror(errno));
	if (setup_sigaction(SIGTERM, SIG_IGN) == -1)
		print_error("sigaction", strerror(errno));
}

void	set_exec_signal_handlers(void)
{
	if (setup_sigaction(SIGINT, SIG_IGN) == -1)
		print_error("sigaction", strerror(errno));
}

void	reset_signal_handlers(void)
{
	if (setup_sigaction(SIGINT, SIG_DFL) == -1)
		print_error("sigaction", strerror(errno));
	if (setup_sigaction(SIGQUIT, SIG_DFL) == -1)
		print_error("sigaction", strerror(errno));
	if (setup_sigaction(SIGTERM, SIG_DFL) == -1)
		print_error("sigaction", strerror(errno));
}
