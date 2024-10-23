/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:24:42 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/02 19:41:08 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include "ast.h"
#include "exec_internal.h"
#include "expansion.h"

static bool	write_heredoc(int read_fd, int write_fd, t_ctx *ctx)
{
	char	*line;
	char	*expanded;

	errno = 0;
	while (true)
	{
		line = get_next_line(read_fd);
		if (line == NULL)
		{
			if (errno)
			{
				print_error("get_next_line", strerror(errno));
				return (false);
			}
			break ;
		}
		expanded = expand_variable_heredoc(line, ctx);
		ft_putstr_fd(expanded, write_fd);
		free(line);
		free(expanded);
	}
	return (true);
}

static int	open_pipe_expanded_heredoc(t_redirect_info *info, t_ctx *ctx)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		print_error("pipe", strerror(errno));
		close(info->heredoc_fd);
		return (-1);
	}
	if (!write_heredoc(info->heredoc_fd, pipe_fd[1], ctx))
	{
		close(info->heredoc_fd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(info->heredoc_fd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	open_tmpfile_expanded_heredoc(t_redirect_info *info, t_ctx *ctx)
{
	int		fd;
	char	tmpfile[TEMPLATE_LEN];

	fd = create_tmpfile(tmpfile, TEMPLATE_LEN, EX_HEREDOC_TMPFILE);
	if (fd == -1)
		return (-1);
	if (!write_heredoc(info->heredoc_fd, fd, ctx))
	{
		close(info->heredoc_fd);
		close(fd);
		unlink(tmpfile);
		return (-1);
	}
	close(info->heredoc_fd);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	return (fd);
}

int	open_heredoc(t_redirect_info *info, t_ctx *ctx)
{
	if (info->heredoc_fd == -1)
		return (-1);
	if (!info->should_expand)
		return (info->heredoc_fd);
	if (info->heredoc_size <= HEREDOC_PIPESIZE)
		return (open_pipe_expanded_heredoc(info, ctx));
	else
		return (open_tmpfile_expanded_heredoc(info, ctx));
}
