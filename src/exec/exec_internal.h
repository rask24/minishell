/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/21 00:01:13 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "env.h"
# include "libft.h"

pid_t	execute_pipeline(t_ast *node, t_env_list *env_list,
			int fd_in, int fd_out);
pid_t	execute_simple_command(t_ast *cmd_node, t_env_list *env_list,
			int fd_int, int fd_out);
bool	handle_redirects(t_list *redirects);

#endif
