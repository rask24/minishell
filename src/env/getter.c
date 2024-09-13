/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:16:13 by yliu              #+#    #+#             */
/*   Updated: 2024/09/13 16:24:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_name(t_env_list *env)
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
