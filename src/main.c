/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/29 16:13:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "env.h"
#include "exec.h"
#include "readline.h"
#include "ui.h"
#include "utils.h"

static t_ctx	*construct_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = ft_xmalloc(sizeof(t_ctx));
	ctx->cwd = getcwd(NULL, 0);
	ctx->env = convert_array_to_env(envp);
	ctx->exit_status = EXIT_SUCCESS;
	return (ctx);
}

static void	destroy_ctx(t_ctx *ctx)
{
	free(ctx->cwd);
	free(ctx);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_ctx			*ctx;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	ctx = construct_ctx(envp);
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
		exec(input, ctx);
		add_history(input);
		free(input);
		restore_terminal_configuration(&original_termios);
	}
	destroy_env_list(ctx->env);
	destroy_ctx(ctx);
	return (EXIT_SUCCESS);
}
