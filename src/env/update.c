/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:07:19 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 23:12:37 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_env_value(t_env_list *env, char *value)
{
	free(get_env_value(env));
	set_env_value(env, value);
	return ;
}
