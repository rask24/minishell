/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 15:36:11 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "expansion.h"
#include "parser_internal.h"
#include "readline.h"
#include "ui.h"
#include "utils.h"

static t_parse_status	calc_heredoc_status(t_list *input_list)
{
	if (input_list && input_list->content == NULL)
		return (PARSE_ABORT);
	else
		return (PARSE_SUCCESS);
}

static void	set_redirect_heredoc_info(t_redirect_info *info, t_list *input_list,
			size_t heredoc_size, bool should_expand)
{
	if (!(input_list && input_list->content == NULL))
		info->heredoc_fd = create_heredoc(input_list, heredoc_size);
	info->heredoc_size = heredoc_size;
	info->should_expand = should_expand;
}

static void	handle_sigint(t_list **input_list)
{
	g_signum = 0;
	ft_lstadd_front(input_list, ft_xlstnew(NULL));
}

static t_list	*read_heredoc_input(const char *delimiter, size_t *heredoc_size)
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
			handle_sigint(&input_list);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		*heredoc_size += ft_strlen(line) + 1;
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	free(line);
	return (input_list);
}

t_parse_status	handle_heredoc(const char *delimiter, t_redirect_info *info)
{
	t_list			*input_list;
	size_t			heredoc_size;
	char			*expanded_delimiter;
	t_parse_status	status;

	expanded_delimiter = expand_quotes((char *)delimiter);
	heredoc_size = 0;
	rl_event_hook = handle_heredoc_sigint_hook;
	input_list = read_heredoc_input(expanded_delimiter, &heredoc_size);
	rl_event_hook = handle_sigint_hook;
	set_redirect_heredoc_info(info, input_list, heredoc_size,
		ft_strcmp(expanded_delimiter, delimiter) == 0);
	status = calc_heredoc_status(input_list);
	free(expanded_delimiter);
	ft_lstclear(&input_list, free);
	return (status);
}
