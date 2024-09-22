/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:16:13 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 10:03:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_key(t_env_list *env)
{
	if (env == NULL)
		return (NULL);
	return (((t_env *)env->content)->key);
}

char	*get_env_value(t_env_list *env)
{
	if (env == NULL)
		return (NULL);
	return (((t_env *)env->content)->value);
}
