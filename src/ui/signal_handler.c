/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:03:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/24 15:24:11 by reasuke          ###   ########.fr       */
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

volatile sig_atomic_t	g_signum = 0;

static void	set_signum(int sig)
{
	g_signum = sig;
}

void	init_signal_handlers(void)
{
	if (signal(SIGINT, set_signum) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
}

void	set_exec_signal_handlers(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		print_error("signal", strerror(errno));
}

void	reset_signal_handlers(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGTERM, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
}
