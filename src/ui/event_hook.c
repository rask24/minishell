/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:34:34 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/18 22:17:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "readline/readline.h"
#include "ui.h"

int	handle_heredoc_sigint_hook(void)
{
	if (g_signum == SIGINT)
		rl_done = 1;
	return (0);
}

int	handle_sigint_hook(void)
{
	if (g_signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}
