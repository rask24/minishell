/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:45:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/20 15:00:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "libft.h"
#include "utils.h"

static bool	handle_redirect_input(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		return (false);
	}
	return (true);
}

static bool	handle_redirect_output(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		return (false);
	}
	return (true);
}

static bool	handle_redirects_append(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		print_error(filepath, strerror(errno));
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		return (false);
	}
	return (true);
}

bool	handle_redirects(t_list *redirects)
{
	int	status;

	status = 0;
	while (redirects)
	{
		if (get_redirect_type(redirects) == REDIRECT_INPUT)
			status = handle_redirect_input(get_redirect_filepath(redirects));
		else if (get_redirect_type(redirects) == REDIRECT_OUTPUT)
			status = handle_redirect_output(get_redirect_filepath(redirects));
		else if (get_redirect_type(redirects) == REDIRECT_APPEND)
			status = handle_redirects_append(get_redirect_filepath(redirects));
		if (status == -1)
			return (false);
		redirects = redirects->next;
	}
	return (true);
}
