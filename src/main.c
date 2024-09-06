/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/06 14:14:58 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "ui.h"
#include "utils.h"

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
		restore_terminal_configuration(&original_termios);
	}
	return (EXIT_SUCCESS);
}
