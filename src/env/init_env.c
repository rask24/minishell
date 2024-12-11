/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:35:41 by yliu              #+#    #+#             */
/*   Updated: 2024/12/11 22:56:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>

#include "builtins.h"
#include "env.h"

#define DFLPATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:."
#define ERRMSG "minishell: warning: shell level (%d) too high, resetting to 1\n"

static void	add_default_path(t_env_list *env_list)
{
	t_list	*tmp;

	tmp = construct_env(ft_xstrdup("PATH"), ft_xstrdup(DFLPATH));
	ft_lstadd_back(&env_list, tmp);
}

static void	add_env_pwd(t_env_list *env_list, char *cwd)
{
	t_list	*tmp;

	if (cwd == NULL)
		return ;
	tmp = construct_env(ft_xstrdup("PWD"), ft_xstrdup(cwd));
	ft_lstadd_back(&env_list, tmp);
}

static int	calc_new_shlvl(const char *shlvl_str)
{
	int		shlvl;
	int		new_shlvl;
	char	*end_ptr;

	errno = 0;
	shlvl = ft_strtol(shlvl_str, &end_ptr, 10);
	if (errno == ERANGE || errno == EINVAL)
		new_shlvl = 1;
	else if (shlvl < 0)
		new_shlvl = 0;
	else if (shlvl >= 999)
	{
		if (*end_ptr == '\0' && shlvl < INT_MAX)
			ft_dprintf(STDERR_FILENO, ERRMSG, shlvl + 1);
		new_shlvl = 1;
	}
	else
		new_shlvl = shlvl + 1;
	return (new_shlvl);
}

static void	deal_shlvl(t_env_list *env_list)
{
	t_list	*tmp;
	char	*shlvl_str;
	int		new_shlvl;

	shlvl_str = lookup_value("SHLVL", env_list);
	if (shlvl_str == NULL)
	{
		tmp = construct_env(ft_xstrdup("SHLVL"), ft_xstrdup("1"));
		ft_lstadd_back(&env_list, tmp);
		return ;
	}
	new_shlvl = calc_new_shlvl(shlvl_str);
	update_env_value(lookup_env("SHLVL", env_list), ft_xitoa(new_shlvl));
}

t_env_list	*init_env(char **envp, char *cwd)
{
	t_env_list	*env_list;

	env_list = convert_array_to_env(envp);
	if (lookup_value("PATH", env_list) == NULL)
		add_default_path(env_list);
	if (lookup_value("PWD", env_list) == NULL)
		add_env_pwd(env_list, cwd);
	deal_shlvl(env_list);
	return (env_list);
}
