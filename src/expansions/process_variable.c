/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:22:14 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:26:24 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static char	*expand_variable(t_expansion *expansions, t_env_list *env)
{
	char	*key;
	char	*value;
	char	*expanded;

	expansions->right++;
	expansions->left++;
	while (*expansions->right && *expansions->right != '$')
		expansions->right++;
	key = ft_xstrndup(expansions->left, expansions->right - expansions->left);
	value = lookup_value(key, env);
	if (!value)
		expanded = ft_xstrdup("");
	else
		expanded = ft_xstrdup(value);
	expansions->left = expansions->right;
	free(key);
	return (expanded);
}

char	*process_variable(t_expansion *expansion, t_env_list *env)
{
	char	*section;

	if (is_start_of_input_(expansion))
		return (expand_variable(expansion, env));
	else
	{
		section = ft_xstrndup(expansion->left, expansion->right
				- expansion->left);
		expansion->left = expansion->right;
		return (section);
	}
}
