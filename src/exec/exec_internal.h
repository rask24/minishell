/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/24 01:29:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "env.h"
# include "libft.h"

# define CMD_NOT_FOUND "command not found"

typedef enum e_exit_status
{
	EXIT_OTHER_ERR = 126,
	EXIT_NOT_FOUND_ERR = 127,
}	t_exit_status;

pid_t	execute_pipeline(t_ast *node, t_env_list *env_list,
			int fd_in, int fd_out);
int		execute_simple_command(t_ast *cmd_node, t_env_list *env_list,
			int fd_int, int fd_out);
bool	handle_redirects(t_list *redirects);
void	wait_for_children(pid_t last_pid);

#endif
