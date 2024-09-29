/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:50 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 10:17:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

static char	*skip_quotes(t_expand_info *expand_info, char c)
{
	expand_info->right++;
	while (*expand_info->right && *expand_info->right != c)
		expand_info->right++;
	expand_info->right++;
	return (trim(expand_info));
}

char	*expand_variable(char *string, t_ctx *ctx)
{
	t_expand_info	expand_info;
	char			*expanded;
	char			*result;

	construct_expand_info(string, &expand_info);
	result = NULL;
	while (*expand_info.right)
	{
		if (*expand_info.right == '\'' || *expand_info.right == '\"')
			expanded = skip_quotes(&expand_info, *expand_info.right);
		else if (*expand_info.right == '$')
			expanded = get_expanded_variable(&expand_info, ctx);
		else
			expanded = trim_till(&expand_info, "$");
		result = ft_xstrjoin2(result, expanded);
		free(expanded);
	}
	return (result);
}
