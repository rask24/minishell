/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:50 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 16:17:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

static char	*trim_single_quotes(t_expand_info *expand_info)
{
	expand_info->right++;
	while (*expand_info->right && *expand_info->right != '\'')
		expand_info->right++;
	expand_info->right++;
	return (trim(expand_info));
}

static const char	*construct_lookup(bool is_smart_expand)
{
	if (is_smart_expand)
		return ("$\'");
	else
		return ("$");
}

char	*expand_variable(char *input, t_ctx *ctx, bool is_smart_expand)
{
	t_expand_info	*expand_info;
	char			*trimmed;
	char			*expanded;
	const char		*lookup;

	lookup = construct_lookup(is_smart_expand);
	expand_info = construct_string_struct(input);
	expanded = NULL;
	while (*expand_info->right)
	{
		if (*expand_info->right == '\'' && is_smart_expand)
			trimmed = trim_single_quotes(expand_info);
		else if (*expand_info->right == '$')
			trimmed = trim_expanded_variable(expand_info, ctx);
		else
			trimmed = trim_till(expand_info, lookup);
		expanded = ft_xstrjoin2(expanded, trimmed);
		free(trimmed);
	}
	destroy_string_struct(expand_info);
	return (expanded);
}
