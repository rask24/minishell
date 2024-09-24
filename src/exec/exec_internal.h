/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/24 16:08:44 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "env.h"
# include "libft.h"

# define CMD_NOT_FOUND "command not found"

typedef struct s_pipeline_conf
{
	int		fd_in;
	int		fd_out;
	int		pipe_read;
	int		pipe_write;
	bool	is_last;
}	t_pipeline_conf;

typedef enum e_exit_status
{
	EXIT_OTHER_ERR = 126,
	EXIT_NOT_FOUND_ERR = 127,
}	t_exit_status;

int		execute_ast_node(t_ast *node, t_env_list *env_list,
			t_pipeline_conf *conf);
int		execute_pipeline(t_ast *node, t_env_list *env_list,
			t_pipeline_conf *conf);
int		execute_command(t_ast *cmd_node, t_env_list *env_list,
			t_pipeline_conf *conf);
bool	handle_redirects(t_list *redirects);
void	wait_for_children(pid_t last_pid);

#endif
