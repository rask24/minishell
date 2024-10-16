/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_array_to_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:35:42 by yliu              #+#    #+#             */
/*   Updated: 2024/10/16 21:30:15 by yliu             ###   ########.fr       */
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

t_env_list	*convert_array_to_env(char **envp)
{
	char		*equal_ptr;
	char		*name;
	char		*value;
	t_env_list	*env_list;

	env_list = NULL;
	while (*envp)
	{
		equal_ptr = ft_strchr(*envp, '=');
		name = ft_xstrndup(*envp, equal_ptr - *envp);
		value = ft_xstrdup(equal_ptr + 1);
		ft_lstadd_back(&env_list, construct_env(name, value));
		envp++;
	}
	if (lookup_value("PATH", env_list) == NULL)
		add_default_path(env_list);
	return (env_list);
}
