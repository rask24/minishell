/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:38:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/28 16:02:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "parser_internal.h"
#include "readline.h"
#include "utils.h"

static int	open_heredoc_tmpfile(void)
{
	int		fd;
	char	*paths[5];
	char	*path;
	int		i;

	paths[0] = "/tmp/";
	paths[1] = "/var/tmp/";
	paths[2] = "/usr/tmp/";
	paths[3] = "./";
	paths[4] = NULL;
	i = 0;
	while(paths[i])
	{
		path = ft_xstrjoin(paths[i], HEREDOC_TMPFILE);
		fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
		free(path);
		if (fd != -1)
			break ;
		i++;
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
		fd = open(HEREDOC_TMPFILE, O_RDONLY);
		unlink(HEREDOC_TMPFILE);
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