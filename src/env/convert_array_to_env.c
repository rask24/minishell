/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_array_to_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:35:42 by yliu              #+#    #+#             */
/*   Updated: 2024/09/18 20:11:26 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

t_env_list	*convert_array_to_env(char **envp)
{
	t_env_list	*env_list;
	char		*equal_ptr;
	char		*name;
	char		*value;

	env_list = NULL;
	while (*envp)
	{
		equal_ptr = ft_strchr(*envp, '=');
		name = ft_xstrndup(*envp, equal_ptr - *envp);
		value = ft_xstrdup(equal_ptr + 1);
		ft_lstadd_back(&env_list, construct_env(name, value));
		envp++;
	}
	return (env_list);
}
