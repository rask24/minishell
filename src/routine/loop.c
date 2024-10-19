/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:12:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/19 16:15:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "ctx.h"
#include "exec.h"
#include "readline.h"
#include "ui.h"

void	loop(t_ctx *ctx)
{
	char			*input;
	struct termios	original_termios;

	rl_signal_event_hook = handle_sigint_hook;
	save_termios(&original_termios);
	while (true)
	{
		init_signal_handlers();
		input = readline(PROMPT);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue ;
		}
		exec(input, ctx);
		add_history(input);
		free(input);
		restore_termios(&original_termios);
	}
}
