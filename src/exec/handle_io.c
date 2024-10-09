/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:45:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/09 20:16:28 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "ctx.h"
#include "exec_internal.h"

static void	handle_pipeline(t_pipe_conf *conf)
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

bool	handle_io(t_pipe_conf *conf, t_list *redirects, t_ctx *ctx)
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
