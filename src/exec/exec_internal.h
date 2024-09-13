/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/13 17:33:27 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "libft.h"

typedef struct s_pipelne_info
{
	int	fd_in;
	int	fd_out;
}	t_pipeline_info;

pid_t	execute_pipeline(t_ast *ast, char **envp, int fd_in, int fd_out);
pid_t	execute_simple_command(t_ast *cmd_node, char **envp,
			t_pipeline_info *info);
int		handle_redirects(t_list *redirects);

#endif
