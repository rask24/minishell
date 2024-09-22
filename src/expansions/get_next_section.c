/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:54 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:34:43 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static char	*process_noexpansion(t_expansion *expansions, t_env_list *env)
{
	expansions->right++;
	return (get_next_section(expansions, env));
}

static char	*process_eof(t_expansion *expansions)
{
	char	*section;

	if (is_start_of_input_(expansions))
		return (ft_xstrdup(""));
	section = ft_xstrdup(expansions->left);
	expansions->left = expansions->right;
	return (section);
}

char	*get_next_section(t_expansion *expansions, t_env_list *env)
{
	if (!*expansions->right)
		return (process_eof(expansions));
	else if (*expansions->right == '$')
		return (process_variable(expansions, env));
	else if (*expansions->right == '\'')
		return (process_single_quote(expansions));
	else
		return (process_noexpansion(expansions, env));
}
