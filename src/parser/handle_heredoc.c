/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/27 01:14:14 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "parser_internal.h"
#include "readline.h"
#include "utils.h"

static int	open_heredoc_tmpfile(void)
{
	int	fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		print_error("open", strerror(errno));
		return (-1);
	}
	return (fd);
}

static void	write_heredoc(int fd, t_list *input_list)
{
	t_list	*node;

	node = input_list;
	while (node != NULL)
	{
		ft_putendl_fd(node->content, fd);
		node = node->next;
	}
	ft_lstclear(&input_list, free);
}

static int	open_heredoc(t_list *input_list, size_t heredoc_size)
{
	int	pipe_fd[2];
	int	fd;

	if (heredoc_size <= HEREDOC_PIPESIZE)
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
	{
		fd = open_heredoc_tmpfile();
		if (fd == -1)
			return (-1);
		write_heredoc(fd, input_list);
		close(fd);
		fd = open("heredoc", O_RDONLY | O_CLOEXEC, S_IRUSR | S_IWUSR);
		unlink("heredoc");
		return (fd);
	}
}

int	handle_heredoc(const char *delimiter)
{
	char	*line;
	t_list	*input_list;
	size_t	heredoc_size;

	input_list = NULL;
	heredoc_size = 0;
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			print_heredoc_warning(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		heredoc_size += ft_strlen(line) + 1;
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	return (open_heredoc(input_list, heredoc_size));
}
