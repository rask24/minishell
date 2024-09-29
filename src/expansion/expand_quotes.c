/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:59:47 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 13:43:30 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static char	*remove_quotes(t_expand_info *expand_info, char q)
{
	char	*unquoted;
	char	quote[2];

	quote[0] = q;
	quote[1] = '\0';
	consume_char(expand_info);
	unquoted = trim_till(expand_info, quote);
	consume_char(expand_info);
	return (unquoted);
}

char	*expand_quotes(char *input)
{
	t_expand_info	*expand_info;
	char			*unquoted;
	char			*expanded;

	expand_info = construct_expand_info(input);
	expanded = NULL;
	while (*expand_info->right)
	{
		if (*expand_info->right == '\'' || *expand_info->right == '\"')
			unquoted = remove_quotes(expand_info, *expand_info->right);
		else
			unquoted = trim_till(expand_info, "\'\"");
		expanded = ft_xstrjoin2(expanded, unquoted);
		free(unquoted);
	}
	destroy_expand_info(expand_info);
	return (expanded);
}
