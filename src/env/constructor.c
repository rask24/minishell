/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:31:39 by yliu              #+#    #+#             */
/*   Updated: 2024/09/13 16:18:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	*construct_env(char *name, char *value)
{
	t_env_list	*env;
	t_env		*content;

	content = (t_env *)ft_xmalloc(sizeof(t_env));
	content->key = name;
	content->value = value;
	env = ft_xlstnew(content);
	return (env);
}
