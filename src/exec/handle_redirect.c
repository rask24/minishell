/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:08:14 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/06 16:44:29 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "exec_internal.h"
#include "expansion.h"
#include "libft.h"

static int	open_redirect_file(t_redirect_info *info, t_ctx *ctx)
{
	int	fd;

	if (info->type == REDIRECT_INPUT)
		fd = open(info->file_or_delim, O_RDONLY);
	else if (info->type == REDIRECT_OUTPUT)
		fd = open(info->file_or_delim, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (info->type == REDIRECT_APPEND)
		fd = open(info->file_or_delim, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (info->type == REDIRECT_HEREDOC)
		fd = open_heredoc(info, ctx);
	else
		fd = -1;
	return (fd);
}

static const char	*expand_filepath(t_list *redirect, t_ctx *ctx)
{
	t_list		*original;
	t_list		*files;
	const char	*ret;

	if (get_redirect_type(redirect) == REDIRECT_HEREDOC)
		return (ft_xstrdup(get_redirect_file_or_delim(redirect)));
	original = ft_xlstnew(ft_xstrdup(get_redirect_file_or_delim(redirect)));
	files = expand(original, ctx);
	ft_lstclear(&original, free);
	if (ft_lstsize(files) == 1)
		ret = ft_xstrdup(files->content);
	else
		ret = NULL;
	ft_lstclear(&files, free);
	return (ret);
}

static void	redirect_std_fd(t_redirect_type type, int fd)
{
	if (type == REDIRECT_INPUT || type == REDIRECT_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			print_error("dup2", strerror(errno));
	}
	else if (type == REDIRECT_OUTPUT || type == REDIRECT_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			print_error("dup2", strerror(errno));
	}
}

bool	handle_redirect(t_list *redirect, t_ctx *ctx)
{
	int			fd;
	const char	*filepath;

	filepath = get_redirect_file_or_delim(redirect);
	set_file_or_delim(redirect, expand_filepath(redirect, ctx));
	if (get_redirect_file_or_delim(redirect) == NULL)
	{
		print_error(filepath, "ambiguous redirect");
		free((char *)filepath);
		return (false);
	}
	fd = open_redirect_file(redirect->content, ctx);
	if (fd == -1)
	{
		if (get_redirect_type(redirect) != REDIRECT_HEREDOC)
			print_error(get_redirect_file_or_delim(redirect), strerror(errno));
		free((char *)filepath);
		return (false);
	}
	redirect_std_fd(get_redirect_type(redirect), fd);
	close(fd);
	free((char *)filepath);
	return (true);
}
