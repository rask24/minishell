/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:18:33 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/25 18:12:45 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"

int	execute_command(t_ast *node, t_ctx *ctx, t_pipeline_conf *conf)
{
	char *cmd_name;
	char **cmd_array;

	cmd_name = node->cmd_args->content;
	cmd_array = convert_cmd_args_to_array(node->cmd_args);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return(builtins_cd(cmd_array, ctx));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtins_pwd(cmd_array, ctx));
	if (ft_strcmp(cmd_name, "echo") == 0)
		return(builtins_echo(cmd_array, ctx));
	else if (ft_strcmp(cmd_name, "env") == 0)
		return(builtins_env(cmd_array, ctx));
	else if (ft_strcmp(cmd_name, "export") == 0)
		return(builtins_export(cmd_array, ctx));
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return(builtins_unset(cmd_array, ctx));
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return(builtins_exit(cmd_array, ctx));
	return (spawn_command(node, ctx, conf));
}
