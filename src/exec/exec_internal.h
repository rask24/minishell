/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/16 17:39:53 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <stdbool.h>

# include "ast.h"
# include "builtins.h"
# include "ctx.h"
# include "env.h"
# include "libft.h"

# define CMD_NOT_FOUND "command not found"

typedef struct s_pipe_conf
{
	int	prev_read;
	int	prev_write;
	int	next_read;
	int	next_write;
}	t_pipe_conf;

typedef enum e_exit_status
{
	EXIT_OTHER_ERR = 126,
	EXIT_NOT_FOUND_ERR = 127,
}	t_exit_status;

int		execute_ast_node(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);
int		execute_and_or(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);
int		execute_pipeline(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);
int		execute_subshell(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);
int		execute_command(t_ast *cmd_node, t_ctx *ctx, t_pipe_conf *conf);
void	close_pipe_fd(t_pipe_conf *conf);
bool	handle_io(t_pipe_conf *conf, t_list *redirects, t_ctx *ctx,
			bool is_forked);
bool	handle_redirect(t_list *redirects, t_ctx *ctx);
int		open_heredoc(t_redirect_info *info, t_ctx *ctx);
void	wait_for_children(void);
void	wait_for_children_with_last_status(pid_t last_pid, t_ctx *ctx);
int		spawn_command(t_ast *node, t_ctx *ctx, t_pipe_conf *conf);

#endif
