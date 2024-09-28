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

static bool	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

static void	push_io(int *fd_array)
{
	fd_array[0] = dup(STDIN_FILENO);
	if (fd_array[0] == -1)
		perror("minishell: dup");
	fd_array[1] = dup(STDOUT_FILENO);
	if (fd_array[1] == -1)
		perror("minishell: dup");
	fd_array[2] = dup(STDERR_FILENO);
	if (fd_array[2] == -1)
		perror("minishell: dup");
}

static void	pop_io(int *fd_array)
{
	if (dup2(fd_array[0], STDIN_FILENO) == -1)
		perror("minishell: dup2");
	if (dup2(fd_array[1], STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	if (dup2(fd_array[2], STDERR_FILENO) == -1)
		perror("minishell: dup2");
	close(fd_array[0]);
	close(fd_array[1]);
	close(fd_array[2]);
}

static int	execute_builtin_command(t_ast *node, t_ctx *ctx)
{
	char	*cmd_name;
	char	**argv;
	int		status;

	status = 0;
	cmd_name = node->cmd_args->content;
	argv = convert_cmd_args_to_array(node->cmd_args);
	if (!argv)
		return (EXIT_FAILURE);
	if (ft_strcmp(cmd_name, "cd") == 0)
		status = builtins_cd(argv, ctx);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		status = builtins_pwd(argv, ctx);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		status = builtins_echo(argv, ctx);
	else if (ft_strcmp(cmd_name, "env") == 0)
		status = builtins_env(argv, ctx);
	else if (ft_strcmp(cmd_name, "export") == 0)
		status = builtins_export(argv, ctx);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		status = builtins_unset(argv, ctx);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		status = builtins_exit(argv, ctx);
	ft_free_strs(argv);
	return (status);
}

int	execute_command(t_ast *node, t_ctx *ctx, t_pipeline_conf *conf)
{
	int	status;
	int	fd_array[3];

	status = 0;
	if (is_builtin(node->cmd_args->content))
	{
		push_io(fd_array);
		handle_io(conf, node->redirects);
		status = execute_builtin_command(node, ctx);
		pop_io(fd_array);
		return (status);
	}
	else
		return (spawn_command(node, ctx, conf));
}
