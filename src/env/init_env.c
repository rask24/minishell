/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:35:41 by yliu              #+#    #+#             */
/*   Updated: 2024/10/16 21:39:00 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#define DFLPATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:."

static void	add_default_path(t_env_list *env_list)
{
	t_list		*tmp;

	tmp = construct_env(ft_xstrdup("PATH"), ft_xstrdup(DFLPATH));
	ft_lstadd_back(&env_list, tmp);
}

t_env_list	*init_env(char **envp)
{
	t_env_list	*env_list;

	env_list = convert_array_to_env(envp);
	if (lookup_value("PATH", env_list) == NULL)
		add_default_path(env_list);
	return (env_list);
}
