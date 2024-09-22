/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:37:58 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 22:01:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		return (ret);
	return (0);
}

static char	*join_path(const char *cwd, const char *dirname)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (cwd[i])
		i++;
	if (i == 0)
		return (ft_xstrdup(dirname));
	else if (cwd[i - 1] == '/')
		tmp = ft_xstrdup(cwd);
	else
		tmp = ft_xstrjoin(cwd, "/");
	tmp2 = ft_xstrjoin(tmp, dirname);
	free(tmp);
	return (tmp2);
}

int	builtins_cd(char **args, t_builtins_ctx *ctx)
{
	char	*dirname;
	char	*fullpath;
	int		res;

	if (args[1] == NULL)
		return (move_to_home(ctx->env));
	dirname = args[1];
	if (dirname[0] == '/')
		fullpath = dirname;
	else
		fullpath = join_path(ctx->cwd, dirname);
	res = chdir(fullpath);
	if (res == -1)
	{
		print_error("chdir", "no such file or directory");
		return (EXIT_FAILURE);
	}
	free(ctx->cwd);
	ctx->cwd = fullpath;
	return (res);
}
