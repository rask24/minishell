/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/20 14:39:34 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "readline.h"
#include "ui.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_env_list		*env_list;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	env_list = convert_array_to_env(envp);
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
		exec(input, env_list);
		add_history(input);
		free(input);
		restore_terminal_configuration(&original_termios);
	}
	return (EXIT_SUCCESS);
}
