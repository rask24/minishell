/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:45:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/26 14:15:08 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "libft.h"
#include "utils.h"

static int	open_redirect_file(t_redirect_type type, const char *filepath)
{
	int				fd;

	if (type == REDIRECT_INPUT)
		fd = open(filepath, O_RDONLY | O_CLOEXEC);
	else if (type == REDIRECT_OUTPUT)
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == REDIRECT_APPEND)
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = -1;
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return (-1);
	}
	return (fd);
}

static void	handle_redirect(t_list *redirects)
{
	int				fd;
	int				std_fd;
	t_redirect_type	type;
	const char		*filepath;

	filepath = get_redirect_filepath(redirects);
	type = get_redirect_type(redirects);
	fd = open_redirect_file(type, filepath);
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return ;
	}
	if (type == REDIRECT_OUTPUT || type == REDIRECT_APPEND)
		std_fd = STDOUT_FILENO;
	else
		std_fd = STDIN_FILENO;
	if (dup2(fd, std_fd) == -1)
		print_error("dup2", strerror(errno));
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

void	handle_io(t_pipeline_conf *conf, t_list *redirects)
{
	handle_pipeline(conf);
	while (redirects)
	{
		handle_redirect(redirects);
		redirects = redirects->next;
	}
}