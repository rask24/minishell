/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:45:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/16 17:19:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "ctx.h"
#include "exec_internal.h"

/*
** next_read should be closed only if the process is forked
*/
static void	handle_pipeline(t_pipe_conf *conf, bool is_forked)
{
	if (conf == NULL)
		return ;
	if (conf->prev_read != STDIN_FILENO)
	{
		if (dup2(conf->prev_read, STDIN_FILENO) == -1)
			print_error("dup2", strerror(errno));
		close(conf->prev_read);
	}
	if (conf->next_write != STDOUT_FILENO)
	{
		if (dup2(conf->next_write, STDOUT_FILENO) == -1)
			print_error("dup2", strerror(errno));
		close(conf->next_write);
	}
	if (is_forked && conf->next_read != -1)
		close(conf->next_read);
}

bool	handle_io(t_pipe_conf *conf, t_list *redirects, t_ctx *ctx,
			bool is_forked)
{
	if (conf)
		handle_pipeline(conf, is_forked);
	while (redirects)
	{
		if (!handle_redirect(redirects, ctx))
			return (false);
		redirects = redirects->next;
	}
	return (true);
}
