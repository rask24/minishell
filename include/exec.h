/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:48 by yliu              #+#    #+#             */
/*   Updated: 2024/10/19 16:22:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ctx.h"
# include "env.h"

typedef struct s_pipe_conf
{
	int	prev_read;
	int	prev_write;
	int	next_read;
	int	next_write;
}	t_pipe_conf;

int	execute_ast_node(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);

#endif
