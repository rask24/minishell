/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/03 20:52:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>

#include "expansion.h"
#include "parser_internal.h"
#include "readline.h"
#include "utils.h"

static void	write_heredoc(int fd, t_list *input_list)
{
	t_list	*node;

	node = input_list;
	while (node)
	{
		ft_putendl_fd(node->content, fd);
		node = node->next;
	}
	ft_lstclear(&input_list, free);
}

static int	open_heredoc_tmpfile(t_list *input_list)
{
	int		fd;
	char	tmpfile[TEMPLATE_LEN];

	fd = create_tmpfile(tmpfile, TEMPLATE_LEN, HEREDOC_TMPFILE);
	if (fd == -1)
		return (-1);
	write_heredoc(fd, input_list);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	return (fd);
}

static int	open_heredoc(t_list *input_list, size_t heredoc_size)
{
	int	pipe_fd[2];

	if (heredoc_size == 0)
		return (open("/dev/null", O_RDONLY));
	else if (heredoc_size <= HEREDOC_PIPESIZE)
	{
		if (pipe(pipe_fd) == -1)
		{
			print_error("pipe", strerror(errno));
			return (-1);
		}
		write_heredoc(pipe_fd[1], input_list);
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else
		return (open_heredoc_tmpfile(input_list));
}

static void	set_redirect_heredoc_info(t_redirect_info *info, t_list *input_list,
			size_t heredoc_size, bool should_expand)
{
	info->heredoc_fd = open_heredoc(input_list, heredoc_size);
	info->heredoc_size = heredoc_size;
	info->should_expand = should_expand;
}

void	handle_heredoc(const char *delimiter, t_redirect_info *info)
{
	char	*line;
	t_list	*input_list;
	size_t	heredoc_size;
	char	*expanded;

	input_list = NULL;
	heredoc_size = 0;
	expanded = expand_quotes((char *)delimiter);
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			print_heredoc_warning(delimiter);
			break ;
		}
		if (ft_strcmp(line, expanded) == 0)
			break ;
		heredoc_size += ft_strlen(line) + 1;
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	set_redirect_heredoc_info(info, input_list, heredoc_size,
		ft_strcmp(expanded, delimiter) == 0);
	free(line);
	free(expanded);
}
