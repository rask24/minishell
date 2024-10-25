/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:52:34 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 13:09:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_a_export(void *content)
{
	t_env	*env_item;

	env_item = (t_env *)content;
	if (env_item->is_valid_value)
		ft_printf("declare -x %s=\"%s\"\n", env_item->key, env_item->value);
	else
		ft_printf("declare -x %s\n", env_item->key);
}

bool	cmp_func(t_env_list *a, t_env_list *b)
{
	return (ft_strcmp(get_env_key(a), get_env_key(b)) > 0);
}

void	print_error_export(const char *input)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_xstrjoin("`", input);
	error_msg = ft_xstrjoin(tmp, "': not a valid identifier");
	free(tmp);
	print_error("export", error_msg);
	free(error_msg);
}
