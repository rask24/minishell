/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:54:41 by yliu              #+#    #+#             */
/*   Updated: 2024/09/20 21:53:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void set_env_value(t_env_list *env, char *value)
{
	((t_env *)env->content)->value = value;
}

void set_env_is_valid_value(t_env_list *env, bool is_valid_value)
{
	((t_env *)env->content)->is_valid_value = is_valid_value;
}
