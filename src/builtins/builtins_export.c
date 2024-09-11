/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:00 by yliu              #+#    #+#             */
/*   Updated: 2024/09/11 14:43:35 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_a_export(void *content)
{
	printf("declare -x %s=\"%s\"\n", ((t_env *)content)->name,
		((t_env *)content)->value);
}

static bool	cmp_func(t_env_list *a, t_env_list *b)
{
	return (ft_strcmp(get_env_name(a), get_env_name(b)) > 0);
}

int	builtins_export(char **args, t_config *config)
{
	(void)args;
	ft_lstsort(&config->env, cmp_func);
	ft_lstiter(config->env, print_a_export);
	return (EXIT_SUCCESS);
}
