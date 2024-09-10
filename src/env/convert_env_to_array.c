/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:32:41 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 12:31:36 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**convert_env_to_array(t_env_list *env)
{
	char	**env_array;
	char	**ans_array;

	env_array = (char **)ft_xmalloc(sizeof(char *) * (ft_lstsize(env) + 1));
	ans_array = env_array;
	while (env)
	{
		*env_array = ft_xstrjoin(get_env_name(env),
				ft_xstrjoin("=", get_env_value(env)));
		env = env->next;
		env_array++;
	}
	return (ans_array);
}
