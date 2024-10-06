/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:37:58 by yliu              #+#    #+#             */
/*   Updated: 2024/10/06 13:56:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "builtins_cd_internal.h"

static int	handle_error(const char *strerror, char *dirname, char *full_path)
{
	char	*error_msg;
	char	*tmp;

	tmp = ft_xstrjoin(dirname, ": ");
	error_msg = ft_xstrjoin(tmp, strerror);
	free(tmp);
	print_error("cd", error_msg);
	free(error_msg);
	free(full_path);
	return (EXIT_FAILURE);
}

static int	move_to_home(t_ctx *ctx)
{
	char	*home_dir;
	int		ret;

	home_dir = lookup_value("HOME", ctx->env);
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
	free(ctx->cwd);
	ctx->cwd = ft_xstrdup(home_dir);
	return (0);
}

static char	*join_path(const char *cwd, const char *dirname)
{
	char	*path_with_slash;
	char	*tmp;
	char	*full_path;

	if (cwd[ft_strlen(cwd) - 1] == '/')
		path_with_slash = ft_xstrdup(cwd);
	else
		path_with_slash = ft_xstrjoin(cwd, "/");
	if (dirname[ft_strlen(dirname) - 1] == '/')
		full_path = ft_xstrjoin(path_with_slash, dirname);
	else
	{
		tmp = ft_xstrjoin(dirname, "/");
		full_path = ft_xstrjoin(path_with_slash, tmp);
		free(tmp);
	}
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
	char	*good_full_path;
	int		res;

	if (args[1] == NULL)
		return (move_to_home(ctx));
	if (args[2] != NULL)
		return (print_error("cd", "too many arguments"), EXIT_FAILURE);
	dirname = args[1];
	if (dirname[0] == '/')
		fullpath = ft_xstrdup(dirname);
	else
		fullpath = join_path(ctx->cwd, dirname);
	good_full_path = remove_long_path(fullpath);
	free(fullpath);
	res = chdir(good_full_path);
	if (res == -1)
		return (handle_error(strerror(errno), dirname, good_full_path));
	free(ctx->cwd);
	remove_last_slash(&good_full_path);
	ctx->cwd = good_full_path;
	return (res);
}
