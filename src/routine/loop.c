/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:12:25 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/19 16:23:31 by reasuke          ###   ########.fr       */
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
		return ;
	}
	if (execute_ast_node(node, ctx, NULL) == EXIT_FAILURE)
		print_error(__func__, "failed to execute command");
	destroy_token_list(token_list);
	destroy_ast(node);
}

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
