/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_array_to_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:35:42 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 14:39:14 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	*convert_array_to_env(char **envp)
{
	t_env_list	*env_list;
	char		*equal_index;
	char		*name;
	char		*value;

	env_list = NULL;
	while (*envp)
	{
		equal_index = ft_strchr(*envp, '=');
		name = ft_strndup(*envp, equal_index - *envp);
		value = ft_strdup(equal_index + 1);
		ft_lstadd_back(&env_list, construct_env(name, value));
		envp++;
	}
	return (env_list);
}
