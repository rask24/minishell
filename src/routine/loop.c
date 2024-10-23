/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:12:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/21 15:50:15 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "ast.h"
#include "ctx.h"
#include "exec.h"
#include "lexer.h"
#include "parser.h"
#include "readline.h"
#include "token.h"
#include "ui.h"

static bool	is_valid_last_token(t_token_list *last_token)
{
	if (last_token == NULL)
		return (false);
	if (get_token_type(last_token) == TOKEN_UNTERMINATED_QUOTE)
	{
		print_error("unterminated quote", get_token_value(last_token));
		return (false);
	}
	if (get_token_type(last_token) == TOKEN_UNKNOWN)
	{
		print_error("unknown token", get_token_value(last_token));
		return (false);
	}
	return (true);
}

static void	exec(char *input, t_ctx *ctx)
{
	t_token_list	*token_list;
	t_ast			*node;

	token_list = lexer(input);
	if (!is_valid_last_token(ft_lstlast(token_list)))
	{
		destroy_token_list(token_list);
		return ;
	}
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		ctx->exit_status = 2;
		return ;
	}
	if (execute_ast_node(node, ctx, NULL) == EXIT_FAILURE)
	{
		print_error(__func__, "failed to execute command");
		wait_children();
	}
	destroy_token_list(token_list);
	destroy_ast(node);
}

static bool	is_empty_input(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " \t\n");
	if (ft_strcmp(trimmed_input, "") == 0)
	{
		free(trimmed_input);
		free(input);
		return (true);
	}
	free(trimmed_input);
	return (false);
}

static void	set_signal_exit_status(t_ctx *ctx)
{
	if (g_signum)
	{
		ctx->exit_status = 128 + g_signum;
		g_signum = 0;
	}
}

void	loop(t_ctx *ctx)
{
	char			*input;
	struct termios	original_termios;

	rl_event_hook = handle_sigint_hook;
	save_termios(&original_termios);
	while (true)
	{
		init_signal_handlers();
		set_signal_exit_status(ctx);
		input = readline(PROMPT);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (is_empty_input(input))
			continue ;
		exec(input, ctx);
		add_history(input);
		free(input);
		restore_termios(&original_termios);
	}
}
