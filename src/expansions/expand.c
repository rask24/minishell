/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:59:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:30:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static void	add_back(char **res, char *new_item)
{
	char	*new_res;

	new_res = ft_xstrjoin(*res, new_item);
	free(*res);
	free(new_item);
	*res = new_res;
}

char	*expand(char *input, t_env_list *env)
{
	char		*new_input;
	t_expansion	expansions;
	char		*section;

	new_input = NULL;
	construct_expansions(input, &expansions);
	while (true)
	{
		section = get_next_section(&expansions, env);
		add_back(&new_input, section);
		if (!*expansions.left)
			break ;
	}
	return (new_input);
}
