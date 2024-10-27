/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/27 10:28:45 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expansion.h"
#include "parser_internal.h"
#include "readline/readline.h"
#include "ui.h"
#include "utils.h"

static size_t	calc_heredoc_size(t_list *input_list)
{
	size_t	heredoc_size;
	size_t	line_size;

	heredoc_size = 0;
	while (input_list)
	{
		if (input_list->content == NULL)
			break ;
		line_size = ft_strlen(input_list->content) + 1;
		if (SIZE_MAX - heredoc_size < line_size)
			return (SIZE_MAX);
		heredoc_size += line_size;
		input_list = input_list->next;
	}
	return (heredoc_size);
}

static void	set_redirect_heredoc_info(t_redirect_info *info, t_list *input_list,
				bool should_expand)
{
	size_t	heredoc_size;

	heredoc_size = calc_heredoc_size(input_list);
	if (!(input_list && input_list->content == NULL))
		info->heredoc_fd = create_heredoc(input_list, heredoc_size);
	info->heredoc_size = heredoc_size;
	info->should_expand = should_expand;
}

static t_list	*read_heredoc_input(const char *delimiter)
{
	char	*line;
	t_list	*input_list;

	input_list = NULL;
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			print_heredoc_warning(delimiter);
			break ;
		}
		if (g_signum == SIGINT && line[0] == '\0')
		{
			g_signum = 0;
			ft_lstadd_front(&input_list, ft_xlstnew(NULL));
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	free(line);
	return (input_list);
}

static t_parse_status	calc_heredoc_status(t_list *input_list)
{
	if (input_list && input_list->content == NULL)
		return (PARSE_ABORT);
	else
		return (PARSE_SUCCESS);
}

t_parse_status	handle_heredoc(const char *delimiter, t_redirect_info *info)
{
	t_list			*input_list;
	char			*expanded_delimiter;
	t_parse_status	status;

	expanded_delimiter = expand_quotes((char *)delimiter);
	rl_event_hook = handle_heredoc_sigint_hook;
	input_list = read_heredoc_input(expanded_delimiter);
	rl_event_hook = handle_sigint_hook;
	set_redirect_heredoc_info(info, input_list,
		ft_strcmp(expanded_delimiter, delimiter) == 0);
	status = calc_heredoc_status(input_list);
	free(expanded_delimiter);
	ft_lstclear(&input_list, free);
	return (status);
}
