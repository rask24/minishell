/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_siglist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:02:30 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/13 17:45:38 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

#include "utils.h"

static void	fill_siglist_first(const char **siglist)
{
	siglist[0] = "Bogus signal";
	siglist[SIGHUP] = "Hangup";
	siglist[SIGINT] = "Interrupt";
	siglist[SIGQUIT] = "Quit";
	siglist[SIGILL] = "Illegal instruction";
	siglist[SIGTRAP] = "BPT trace/trap";
	siglist[SIGABRT] = "ABORT instruction";
	siglist[SIGEMT] = "EMT instruction";
	siglist[SIGFPE] = "Floating point exception";
	siglist[SIGKILL] = "Killed";
	siglist[SIGBUS] = "Bus error";
	siglist[SIGSEGV] = "Segmentation fault";
	siglist[SIGSYS] = "Bad system call";
	siglist[SIGPIPE] = "Broken pipe";
	siglist[SIGALRM] = "Alarm clock";
	siglist[SIGTERM] = "Terminated";
}

static void	fill_siglist_second(const char **siglist)
{
	siglist[SIGURG] = "Urgent IO condition";
	siglist[SIGSTOP] = "Stopped (signal)";
	siglist[SIGTSTP] = "Stopped";
	siglist[SIGCONT] = "Continue";
	siglist[SIGCHLD] = "Child death or stop";
	siglist[SIGTTIN] = "Stopped (tty input)";
	siglist[SIGTTOU] = "Stopped (tty output)";
	siglist[SIGIO] = "I/O ready";
	siglist[SIGXCPU] = "CPU limit";
	siglist[SIGXFSZ] = "File limit";
	siglist[SIGVTALRM] = "Alarm (virtual)";
	siglist[SIGPROF] = "Alarm (profile)";
	siglist[SIGWINCH] = "Window changed";
	siglist[SIGUSR1] = "User signal 1";
	siglist[SIGUSR2] = "User signal 2";
	siglist[SIGINFO] = "Information request";
}

static void	init_siglist(const char **siglist)
{
	int		i;

	i = 0;
	while (i < NSIG)
	{
		siglist[i] = "Unknown signal";
		i++;
	}
	fill_siglist_first(siglist);
	fill_siglist_second(siglist);
}

const char	**create_siglist(void)
{
	const char	**siglist;

	siglist = ft_xmalloc(sizeof(char *) * NSIG);
	init_siglist(siglist);
	return (siglist);
}
