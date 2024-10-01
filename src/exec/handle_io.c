/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:45:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/01 13:37:31 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "expansion.h"
#include "libft.h"
#include "utils.h"

static int	open_redirect_file(t_redirect_type type, const char *filepath
				, int heredoc_fd)
{
	int	fd;

	if (type == REDIRECT_INPUT)
		fd = open(filepath, O_RDONLY);
	else if (type == REDIRECT_OUTPUT)
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == REDIRECT_APPEND)
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == REDIRECT_HEREDOC)
		fd = heredoc_fd;
	else
		fd = -1;
	return (fd);
}

static bool	handle_redirect(t_list *redirects, t_ctx *ctx)
{
	int				fd;
	int				std_fd;
	t_redirect_type	type;
	char			*tmp;
	const char		*filepath;

	tmp = expand_variable((char *)get_redirect_filepath(redirects), ctx);
	filepath = expand_quotes(tmp);
	type = get_redirect_type(redirects);
	fd = open_redirect_file(type, filepath, get_heredoc_fd(redirects));
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return (false);
	}
	if (type == REDIRECT_OUTPUT || type == REDIRECT_APPEND)
		std_fd = STDOUT_FILENO;
	else
		std_fd = STDIN_FILENO;
	if (dup2(fd, std_fd) == -1)
		print_error("dup2", strerror(errno));
	close(fd);
	return (true);
}

static void	handle_pipeline(t_pipeline_conf *conf)
{
	if (conf->fd_in != STDIN_FILENO)
	{
		if (dup2(conf->fd_in, STDIN_FILENO) == -1)
			print_error("dup2", strerror(errno));
		else
			close(conf->fd_in);
	}
	if (conf->fd_out != STDOUT_FILENO)
	{
		if (dup2(conf->fd_out, STDOUT_FILENO) == -1)
			print_error("dup2", strerror(errno));
		else
			close(conf->fd_out);
	}
}

bool	handle_io(t_pipeline_conf *conf, t_list *redirects, t_ctx *ctx)
{
	handle_pipeline(conf);
	while (redirects)
	{
		if (!handle_redirect(redirects, ctx))
			return (false);
		redirects = redirects->next;
	}
	return (true);
}
