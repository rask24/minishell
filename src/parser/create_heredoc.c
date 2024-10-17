/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:29:10 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/17 20:55:05 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

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

int	create_heredoc(t_list *input_list, size_t heredoc_size)
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
