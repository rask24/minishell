/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:31:39 by yliu              #+#    #+#             */
/*   Updated: 2024/09/21 14:55:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	*construct_env(char *key, char *value)
{
	t_env_list	*env;
	t_env		*content;

	content = (t_env *)ft_xmalloc(sizeof(t_env));
	content->key = key;
	content->is_valid_value = true;
	content->value = value;
	env = ft_xlstnew(content);
	return (env);
}

t_env_list	*construct_env_with_bool(char *key, char *value,
							bool is_valid_value)
{
	t_env_list	*env;
	t_env		*content;

	content = (t_env *)ft_xmalloc(sizeof(t_env));
	content->key = key;
	content->is_valid_value = is_valid_value;
	content->value = value;
	env = ft_xlstnew(content);
	return (env);
}
