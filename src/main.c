/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/07 17:35:12 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "readline.h"
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
		exec(input, envp);
		add_history(input);
		free(input);
		restore_terminal_configuration(&original_termios);
	}
	return (EXIT_SUCCESS);
}
