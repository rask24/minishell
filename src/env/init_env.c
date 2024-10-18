/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:35:41 by yliu              #+#    #+#             */
/*   Updated: 2024/10/17 23:14:53 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"

#define DFLPATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:."

static void	add_default_path(t_env_list *env_list)
{
	t_list	*tmp;

	tmp = construct_env(ft_xstrdup("PATH"), ft_xstrdup(DFLPATH));
	ft_lstadd_back(&env_list, tmp);
}

static void	deal_shlvl(t_env_list *env_list)
{
	t_list		*tmp;
	char		*shlvl_str;
	int			shlvl;
	int			new_shlvl;

	shlvl_str = lookup_value("SHLVL", env_list);
	if (shlvl_str == NULL)
	{
		tmp = construct_env(ft_xstrdup("SHLVL"), ft_xstrdup("1"));
		ft_lstadd_back(&env_list, tmp);
		return ;
	}
	shlvl = ft_atoi(shlvl_str);
	if (errno == EINVAL || errno == ERANGE)
		new_shlvl = 1;
	else if (shlvl < 0)
		new_shlvl = 0;
	else if (shlvl >= 999)
	{
		print_error("warning", "shell level (1000) too high, resetting to 1");
		new_shlvl = 1;
	}
	else
		new_shlvl = shlvl + 1;
	update_env_value(is_already_exist("SHLVL", env_list), ft_xitoa(new_shlvl));
}

t_env_list	*init_env(char **envp)
{
	t_env_list	*env_list;

	env_list = convert_array_to_env(envp);
	if (lookup_value("PATH", env_list) == NULL)
		add_default_path(env_list);
	deal_shlvl(env_list);
	return (env_list);
}
