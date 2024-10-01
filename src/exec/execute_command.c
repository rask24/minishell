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
#include "expansion.h"

static bool	is_builtin(const char *cmd_name)
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

static void	save_std_io(int *fd_array)
{
	fd_array[0] = dup(STDIN_FILENO);
	if (fd_array[0] == -1)
		print_error("dup", strerror(errno));
	fd_array[1] = dup(STDOUT_FILENO);
	if (fd_array[1] == -1)
		print_error("dup", strerror(errno));
	fd_array[2] = dup(STDERR_FILENO);
	if (fd_array[2] == -1)
		print_error("dup", strerror(errno));
}

static void	restore_std_io(int *std_fds)
{
	if (dup2(std_fds[0], STDIN_FILENO) == -1)
		print_error("dup2", strerror(errno));
	if (dup2(std_fds[1], STDOUT_FILENO) == -1)
		print_error("dup2", strerror(errno));
	if (dup2(std_fds[2], STDERR_FILENO) == -1)
		print_error("dup2", strerror(errno));
	close(std_fds[0]);
	close(std_fds[1]);
	close(std_fds[2]);
}

static int	execute_builtin_command(t_ast *node, t_ctx *ctx)
{
	const char	*cmd_name;
	char		**argv;
	int			status;

	status = 0;
	cmd_name = get_cmd_arg(node->cmd_args);
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
	int	std_fds[3];

	node->cmd_args = expand(node->cmd_args, ctx);
	if (is_builtin(get_cmd_arg(node->cmd_args)))
	{
		save_std_io(std_fds);
		if (handle_io(conf, node->redirects))
			ctx->exit_status = execute_builtin_command(node, ctx);
		else
			ctx->exit_status = EXIT_FAILURE;
		restore_std_io(std_fds);
		return (EXIT_SUCCESS);
	}
	else
		return (spawn_command(node, ctx, conf));
}
