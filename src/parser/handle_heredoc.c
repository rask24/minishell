/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/17 20:34:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "expansion.h"
#include "parser_internal.h"
#include "readline.h"
#include "utils.h"

static void	set_redirect_heredoc_info(t_redirect_info *info, t_list *input_list,
			size_t heredoc_size, bool should_expand)
{
	info->heredoc_fd = create_heredoc(input_list, heredoc_size);
	info->heredoc_size = heredoc_size;
	info->should_expand = should_expand;
}

void	handle_heredoc(const char *delimiter, t_redirect_info *info)
{
	char	*line;
	t_list	*input_list;
	size_t	heredoc_size;
	char	*expanded_delimiter;

	input_list = NULL;
	heredoc_size = 0;
	expanded_delimiter = expand_quotes((char *)delimiter);
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			print_heredoc_warning(delimiter);
			break ;
		}
		if (ft_strcmp(line, expanded_delimiter) == 0)
			break ;
		heredoc_size += ft_strlen(line) + 1;
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	set_redirect_heredoc_info(info, input_list, heredoc_size,
		ft_strcmp(expanded_delimiter, delimiter) == 0);
	free(line);
	free(expanded_delimiter);
}
