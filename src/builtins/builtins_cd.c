/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:37:58 by yliu              #+#    #+#             */
/*   Updated: 2024/10/05 19:20:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_cd_internal.h"

static void	print_error_cd(const char *dirname, const char *strerror)
{
	char	*error_msg;
	char	*tmp;

	tmp = ft_xstrjoin(dirname, ": ");
	error_msg = ft_xstrjoin(tmp, strerror);
	free(tmp);
	print_error("cd", error_msg);
	free(error_msg);
}

static int	move_to_home(t_env_list *env)
{
	char	*home_dir;
	int		ret;

	home_dir = lookup_value("HOME", env);
	if (!home_dir)
	{
		print_error("cd", "HOME not set");
		return (EXIT_FAILURE);
	}
	ret = chdir(home_dir);
	if (ret == -1)
	{
		print_error("chdir", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

static char	*join_path(const char *cwd, const char *dirname)
{
	char	*path_with_slash;
	char	*full_path;

	if (cwd[ft_strlen(cwd) - 1] == '/')
		path_with_slash = ft_xstrdup(cwd);
	else
		path_with_slash = ft_xstrjoin(cwd, "/");
	full_path = ft_xstrjoin(path_with_slash, dirname);
	free(path_with_slash);
	return (full_path);
}

static void	remove_last_slash(char **fullpath)
{
	size_t	len;

	len = ft_strlen(*fullpath);
	if (len > 1 && (*fullpath)[len - 1] == '/')
		(*fullpath)[len - 1] = '\0';
}

int	builtins_cd(char **args, t_ctx *ctx)
{
	char	*dirname;
	char	*fullpath;
	char	*optimized_full_path;
	int		res;

	if (args[1] == NULL)
		return (move_to_home(ctx->env));
	if (args[2] != NULL)
		return (print_error("cd", "too many arguments"), EXIT_FAILURE);
	dirname = args[1];
	if (dirname[0] == '/')
		fullpath = ft_xstrdup(dirname);
	else
		fullpath = join_path(ctx->cwd, dirname);
	optimized_full_path = remove_long_path(fullpath);
	free(fullpath);
	res = chdir(optimized_full_path);
	if (res == -1)
	{
		print_error_cd(dirname, strerror(errno));
		free(optimized_full_path);
		return (EXIT_FAILURE);
	}
	free(ctx->cwd);
	remove_last_slash(&optimized_full_path);
	ctx->cwd = optimized_full_path;
	return (res);
}
