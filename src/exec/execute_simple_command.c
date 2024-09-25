/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:18:33 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/25 18:12:45 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "libft.h"
#include "ui.h"
#include "utils.h"

static bool	handle_pipeline(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			print_error("dup2", strerror(errno));
			return (false);
		}
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			print_error("dup2", strerror(errno));
			return (false);
		}
		close(fd_out);
	}
	return (true);
}

static bool	is_a_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	return (S_ISDIR(st.st_mode));
}

static char	*search_for_command(char *basename, t_env_list *env_list)
{
	char	**paths;
	char	*joined_path;
	char	*tmp;
	int		i;

	paths = ft_split(lookup_value("PATH", env_list), ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_xstrjoin(paths[i], "/");
		joined_path = ft_xstrjoin(tmp, basename);
		free(tmp);
		if (access(joined_path, X_OK) == 0)
		{
			ft_free_strs(paths);
			return (joined_path);
		}
		free(joined_path);
		i++;
	}
	ft_free_strs(paths);
	return (NULL);
}

static void	execute_command_internal(char **argv, t_env_list *env_list)
{
	char	*cmd_path;

	cmd_path = argv[0];
	if (lookup_value("PATH", env_list) && ft_strchr(cmd_path, '/') == NULL)
	{
		cmd_path = search_for_command(cmd_path, env_list);
		if (cmd_path == NULL)
			print_error_exit(argv[0], CMD_NOT_FOUND, EXIT_NOT_FOUND_ERR);
	}
	if (is_a_directory(cmd_path))
		print_error_exit(cmd_path, strerror(EISDIR), EXIT_OTHER_ERR);
	if (execve(cmd_path, argv, (char **)convert_env_to_array(env_list)) == -1)
	{
		if (errno == ENOENT)
			print_error_exit(argv[0], strerror(errno), EXIT_NOT_FOUND_ERR);
		else
			print_error_exit(argv[0], strerror(errno), EXIT_OTHER_ERR);
	}
}

pid_t	execute_simple_command(t_ast *node, t_env_list *env_list,
			int fd_in, int fd_out)
{
	pid_t		pid;
	char		**argv;

	pid = fork();
	if (pid == -1)
		print_error_exit("fork", strerror(errno), -1);
	else if (pid == 0)
	{
		argv = convert_cmd_args_to_array(node->cmd_args);
		if (!handle_pipeline(fd_in, fd_out))
			exit(EXIT_FAILURE);
		if (!handle_redirects(node->redirects))
			exit(EXIT_FAILURE);
		reset_signal_handlers();
		execute_command_internal(argv, env_list);
	}
	return (pid);
}
